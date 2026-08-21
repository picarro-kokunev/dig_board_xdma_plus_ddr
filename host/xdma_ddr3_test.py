#!/usr/bin/env python3
# xdma_ddr3_test.py
"""
Read/write DDR3 on the dig_board_xdma_plus_ddr design through the Xilinx XDMA driver.

Hardware path (design_1 in project_1/):
  Host PCIe -> XDMA (M_AXI master) -> axi_smc -> mig_7series_0 (S_AXI) -> DDR3

Address map:
  AXI offset 0x00000000 .. 0x3FFFFFFF (1 GiB) -> mig_7series_0/memaddr

DDR3 (from mig_b.prj):
  Device : MT41K256M16XX-107
  Width  : 32-bit
  Size   : 1 GiB

Access method:
  Use the Linux XDMA character devices. lseek() sets the AXI byte address;
  write() on h2c_* transfers host -> card (DDR write), read() on c2h_* reads
  card -> host (DDR read).

Requires the Xilinx XDMA kernel module and device nodes, e.g.:
  /dev/xdma0_h2c_0, /dev/xdma0_c2h_0

Run as root or with read/write permission on those nodes.
"""

from __future__ import annotations

import argparse
import os
import struct
import sys
import time
from pathlib import Path
from typing import Iterable

# Constants derived from project_1/project_1.srcs/sources_1/bd/design_1/design_1.bd
DDR3_AXI_BASE = 0x0000_0000
DDR3_SIZE_BYTES = 1 << 30  # 1 GiB (SEG_mig_7series_0_memaddr range)
DDR3_DATA_WIDTH_BYTES = 4  # 32-bit DDR interface

DEFAULT_XDMA_ID = 0
DEFAULT_H2C_CHANNEL = 0
DEFAULT_C2H_CHANNEL = 0
DEFAULT_CHUNK_BYTES = 1 << 20  # 1 MiB


class XdmaDdr3Error(Exception):
    """Raised when an XDMA/DDR3 operation fails."""


class XdmaDdr3:
    """DDR3 access via XDMA H2C/C2H DMA channels."""

    def __init__(
        self,
        xdma_id: int = DEFAULT_XDMA_ID,
        h2c_channel: int = DEFAULT_H2C_CHANNEL,
        c2h_channel: int = DEFAULT_C2H_CHANNEL,
        chunk_bytes: int = DEFAULT_CHUNK_BYTES,
    ) -> None:
        self.xdma_id = xdma_id
        self.h2c_path = Path(f"/dev/xdma{xdma_id}_h2c_{h2c_channel}")
        self.c2h_path = Path(f"/dev/xdma{xdma_id}_c2h_{c2h_channel}")
        self.chunk_bytes = chunk_bytes
        self._h2c_fd: int | None = None
        self._c2h_fd: int | None = None

    def __enter__(self) -> XdmaDdr3:
        self.open()
        return self

    def __exit__(self, exc_type, exc, tb) -> None:
        self.close()

    def open(self) -> None:
        self._h2c_fd = self._open_device(self.h2c_path, os.O_RDWR, "h2c")
        self._c2h_fd = self._open_device(self.c2h_path, os.O_RDWR, "c2h")

    def close(self) -> None:
        for attr in ("_h2c_fd", "_c2h_fd"):
            fd = getattr(self, attr)
            if fd is not None:
                os.close(fd)
                setattr(self, attr, None)

    @staticmethod
    def _open_device(path: Path, flags: int, label: str) -> int:
        if not path.exists():
            raise XdmaDdr3Error(
                f"Missing XDMA {label} device {path}. "
                "Load the xdma driver and check PCIe enumeration."
            )
        try:
            return os.open(path, flags)
        except OSError as exc:
            raise XdmaDdr3Error(f"Cannot open {path}: {exc}") from exc

    def _check_range(self, address: int, length: int) -> None:
        if address < DDR3_AXI_BASE:
            raise XdmaDdr3Error(f"Address 0x{address:x} is below DDR3 base")
        end = address + length
        limit = DDR3_AXI_BASE + DDR3_SIZE_BYTES
        if end > limit:
            raise XdmaDdr3Error(
                f"Transfer 0x{address:x}+0x{length:x} exceeds DDR3 "
                f"range [0x{DDR3_AXI_BASE:x}, 0x{limit - 1:x}]"
            )
        if address % DDR3_DATA_WIDTH_BYTES:
            raise XdmaDdr3Error(
                f"Address 0x{address:x} is not {DDR3_DATA_WIDTH_BYTES}-byte aligned"
            )
        if length % DDR3_DATA_WIDTH_BYTES:
            raise XdmaDdr3Error(
                f"Length 0x{length:x} is not {DDR3_DATA_WIDTH_BYTES}-byte aligned"
            )

    def write(self, address: int, data: bytes) -> int:
        """Write bytes to DDR3 at the given AXI byte address."""
        if self._h2c_fd is None:
            raise XdmaDdr3Error("Device not open")
        if not data:
            return 0

        self._check_range(address, len(data))
        os.lseek(self._h2c_fd, address, os.SEEK_SET)

        total = 0
        view = memoryview(data)
        while total < len(data):
            chunk = min(self.chunk_bytes, len(data) - total)
            written = os.write(self._h2c_fd, view[total : total + chunk])
            if written <= 0:
                raise XdmaDdr3Error(
                    f"H2C write failed at 0x{address + total:x} after {total} bytes"
                )
            total += written
        return total

    def read(self, address: int, length: int) -> bytes:
        """Read bytes from DDR3 at the given AXI byte address."""
        if self._c2h_fd is None:
            raise XdmaDdr3Error("Device not open")
        if length == 0:
            return b""

        self._check_range(address, length)
        os.lseek(self._c2h_fd, address, os.SEEK_SET)

        chunks: list[bytes] = []
        total = 0
        while total < length:
            chunk = min(self.chunk_bytes, length - total)
            data = os.read(self._c2h_fd, chunk)
            if not data:
                raise XdmaDdr3Error(
                    f"C2H read failed at 0x{address + total:x} after {total} bytes"
                )
            chunks.append(data)
            total += len(data)
        return b"".join(chunks)

    def read_no_data_return(self, address: int, length: int):
        """Read bytes from DDR3 at the given AXI byte address. Do not return anything."""
        if self._c2h_fd is None:
            raise XdmaDdr3Error("Device not open")
        if length == 0:
            return b""

        self._check_range(address, length)
        os.lseek(self._c2h_fd, address, os.SEEK_SET)

        chunks: list[bytes] = []
        total = 0
        while total < length:
            chunk = min(self.chunk_bytes, length - total)
            total += len(os.read(self._c2h_fd, chunk))
        return

    def fill(self, address: int, length: int, pattern: bytes) -> int:
        if not pattern:
            raise XdmaDdr3Error("Pattern must not be empty")
        if len(pattern) % DDR3_DATA_WIDTH_BYTES:
            raise XdmaDdr3Error("Pattern length must be 4-byte aligned")

        block = (pattern * ((self.chunk_bytes // len(pattern)) + 1))[: self.chunk_bytes]
        remaining = length
        offset = address
        written = 0
        while remaining > 0:
            size = min(len(block), remaining)
            size -= size % DDR3_DATA_WIDTH_BYTES
            if size == 0:
                break
            self.write(offset, block[:size])
            written += size
            offset += size
            remaining -= size
        return written

    def verify(self, address: int, expected: bytes) -> tuple[bool, int | None, int | None]:
        """
        Read back memory and compare with expected data.

        Returns (ok, mismatch_offset, expected_value) where mismatch_offset is
        relative to address.
        """
        actual = self.read(address, len(expected))
        if actual == expected:
            return True, None, None

        for index, (got, want) in enumerate(zip(actual, expected)):
            if got != want:
                return False, index, want
        return False, len(actual), None


def parse_hex_bytes(text: str) -> bytes:
    cleaned = text.replace("_", "").replace("0x", "").replace(" ", "")
    if len(cleaned) % 2:
        cleaned = "0" + cleaned
    return bytes.fromhex(cleaned)


def parse_int(value: str) -> int:
    return int(value, 0)


def format_hex_dump(data: bytes, base_address: int = 0, width: int = 16) -> str:
    lines: list[str] = []
    for offset in range(0, len(data), width):
        chunk = data[offset : offset + width]
        hex_part = " ".join(f"{byte:02x}" for byte in chunk)
        ascii_part = "".join(chr(byte) if 32 <= byte < 127 else "." for byte in chunk)
        lines.append(f"{base_address + offset:08x}  {hex_part:<{width * 3}}  {ascii_part}")
    return "\n".join(lines)


def incremental_pattern(length: int, seed: int = 0) -> bytes:
    return bytes((seed + index) & 0xFF for index in range(length))


def walking_ones_pattern(length: int) -> bytes:
    out = bytearray(length)
    for index in range(0, length, DDR3_DATA_WIDTH_BYTES):
        word_index = index // DDR3_DATA_WIDTH_BYTES
        value = 1 << (word_index % 32)
        out[index : index + DDR3_DATA_WIDTH_BYTES] = struct.pack("<I", value)
    return bytes(out)


def run_self_test(ddr: XdmaDdr3, offset: int, size: int) -> None:
    print(f"Self-test: offset=0x{offset:x}, size=0x{size:x}")

    patterns: Iterable[tuple[str, bytes]] = (
        ("incremental", incremental_pattern(size, seed=0xA5)),
        ("walking-ones", walking_ones_pattern(size)),
        ("aa55", b"\xaa\x55\x00\x00" * (size // 4)),
    )

    for name, pattern in patterns:
        print(f"  pattern {name}: write...", end="", flush=True)
        ddr.write(offset, pattern)
        print(" read/verify...", end="", flush=True)
        ok, mismatch, expected = ddr.verify(offset, pattern)
        if ok:
            print(" PASS")
            continue
        raise XdmaDdr3Error(
            f"Pattern {name} failed at +0x{mismatch:x}, expected 0x{expected:02x}"
        )

    print("Self-test PASSED")


def run_bandwidth_test(ddr: XdmaDdr3, offset: int, size: int, iterations: int) -> None:
    payload = incremental_pattern(size, seed=0x5A)
    print(f"Bandwidth test: offset=0x{offset:x}, size=0x{size:x}, iterations={iterations}")

    start = time.perf_counter()
    for _ in range(iterations):
        ddr.write(offset, payload)
    write_elapsed = time.perf_counter() - start

    start = time.perf_counter()
    for _ in range(iterations):
        data = ddr.read(offset, size)
        if data != payload:
            raise XdmaDdr3Error("Readback mismatch during bandwidth test")
    read_elapsed = time.perf_counter() - start

    start = time.perf_counter()
    for _ in range(iterations):
        ddr.read_no_data_return(offset, size)
    read_elapsed_no_verify = time.perf_counter() - start

    write_mbps = (size * iterations / write_elapsed) / (1024 * 1024)
    read_mbps = (size * iterations / read_elapsed) / (1024 * 1024)
    read_mbps_no_verify = (size * iterations / read_elapsed_no_verify) / (1024 * 1024)
    print(f"  write: {write_mbps:.1f} MiB/s ({write_elapsed:.3f} s total)")
    print(f"  read : {read_mbps:.1f} MiB/s ({read_elapsed:.3f} s total)")
    print(f"  read (no verify): {read_mbps_no_verify:.1f} MiB/s ({read_elapsed_no_verify:.3f} s total)")

def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description="Read/write DDR3 through the XDMA AXI master (design_1)."
    )
    parser.add_argument(
        "--xdma-id",
        type=int,
        default=DEFAULT_XDMA_ID,
        help="XDMA device index (default: 0 -> /dev/xdma0_*)",
    )
    parser.add_argument(
        "--h2c-channel",
        type=int,
        default=DEFAULT_H2C_CHANNEL,
        help="H2C DMA channel for writes (default: 0)",
    )
    parser.add_argument(
        "--c2h-channel",
        type=int,
        default=DEFAULT_C2H_CHANNEL,
        help="C2H DMA channel for reads (default: 0)",
    )
    parser.add_argument(
        "--chunk-bytes",
        type=parse_int,
        default=DEFAULT_CHUNK_BYTES,
        help="Max bytes per DMA syscall (default: 1 MiB)",
    )

    sub = parser.add_subparsers(dest="command", required=True)

    read_p = sub.add_parser("read", help="Read DDR3 and print hex dump or save to file")
    read_p.add_argument("--offset", type=parse_int, required=True, help="AXI byte address")
    read_p.add_argument("--length", type=parse_int, required=True, help="Number of bytes")
    read_p.add_argument("--out", type=Path, help="Optional output file")

    write_p = sub.add_parser("write", help="Write hex data or file to DDR3")
    write_p.add_argument("--offset", type=parse_int, required=True, help="AXI byte address")
    src = write_p.add_mutually_exclusive_group(required=True)
    src.add_argument("--hex", help="Hex byte string, e.g. DEADBEEF or 0xde ad be ef")
    src.add_argument("--file", type=Path, help="Binary file to write")

    fill_p = sub.add_parser("fill", help="Fill a region with a repeating pattern")
    fill_p.add_argument("--offset", type=parse_int, required=True)
    fill_p.add_argument("--length", type=parse_int, required=True)
    fill_p.add_argument(
        "--pattern",
        default="0x00000000",
        help="Repeating hex pattern (default: 00 -> 32-bit zero words)",
    )

    verify_p = sub.add_parser("verify", help="Read back and compare with expected data")
    verify_p.add_argument("--offset", type=parse_int, required=True)
    src = verify_p.add_mutually_exclusive_group(required=True)
    src.add_argument("--hex", help="Expected hex bytes")
    src.add_argument("--file", type=Path, help="Expected binary file")

    sub.add_parser("test", help="Run built-in write/read/verify patterns")

    bench_p = sub.add_parser("bench", help="Measure read/write throughput")
    bench_p.add_argument("--offset", type=parse_int, default=0x0)
    bench_p.add_argument("--size", type=parse_int, default=4 * 1024 * 1024)
    bench_p.add_argument("--iterations", type=int, default=10)

    info_p = sub.add_parser("info", help="Print design-derived memory map info")
    info_p.add_argument(
        "--list-devices",
        action="store_true",
        help="List /dev/xdma* nodes present on this host",
    )

    return parser


def cmd_info(args: argparse.Namespace) -> int:
    print("design_1 DDR3 map")
    print(f"  AXI base : 0x{DDR3_AXI_BASE:08x}")
    print(f"  Size     : 0x{DDR3_SIZE_BYTES:x} ({DDR3_SIZE_BYTES // (1024 * 1024)} MiB)")
    print(f"  Width    : {DDR3_DATA_WIDTH_BYTES * 8}-bit")
    print("  Path     : XDMA M_AXI -> axi_smc -> mig_7series_0 S_AXI")
    print(f"  Devices  : /dev/xdma{args.xdma_id}_h2c_{args.h2c_channel}, "
          f"/dev/xdma{args.xdma_id}_c2h_{args.c2h_channel}")

    if args.list_devices:
        nodes = sorted(Path("/dev").glob("xdma*"))
        if nodes:
            print("\nDetected nodes:")
            for node in nodes:
                print(f"  {node}")
        else:
            print("\nNo /dev/xdma* nodes found.")
    return 0


def main(argv: list[str] | None = None) -> int:
    parser = build_parser()
    args = parser.parse_args(argv)

    if args.command == "info":
        return cmd_info(args)

    try:
        with XdmaDdr3(
            xdma_id=args.xdma_id,
            h2c_channel=args.h2c_channel,
            c2h_channel=args.c2h_channel,
            chunk_bytes=args.chunk_bytes,
        ) as ddr:
            if args.command == "read":
                data = ddr.read(args.offset, args.length)
                if args.out:
                    args.out.write_bytes(data)
                    print(f"Read 0x{len(data):x} bytes from 0x{args.offset:x} -> {args.out}")
                else:
                    print(format_hex_dump(data, base_address=args.offset))

            elif args.command == "write":
                payload = parse_hex_bytes(args.hex) if args.hex else args.file.read_bytes()
                count = ddr.write(args.offset, payload)
                print(f"Wrote 0x{count:x} bytes to 0x{args.offset:x}")

            elif args.command == "fill":
                pattern = parse_hex_bytes(args.pattern)
                count = ddr.fill(args.offset, args.length, pattern)
                print(f"Filled 0x{count:x} bytes at 0x{args.offset:x}")

            elif args.command == "verify":
                expected = parse_hex_bytes(args.hex) if args.hex else args.file.read_bytes()
                ok, mismatch, expected_byte = ddr.verify(args.offset, expected)
                if ok:
                    print(f"Verify PASS at 0x{args.offset:x}, length 0x{len(expected):x}")
                else:
                    print(
                        f"Verify FAIL at 0x{args.offset + mismatch:x} "
                        f"(+0x{mismatch:x}), expected 0x{expected_byte:02x}"
                    )
                    return 1

            elif args.command == "test":
                run_self_test(ddr, offset=0x0, size=64 * 1024)
                run_self_test(ddr, offset=0x10_0000, size=64 * 1024)
                run_self_test(ddr, offset=0x0, size=64 *1024 * 1024)

            elif args.command == "bench":
                run_bandwidth_test(ddr, args.offset, args.size, args.iterations)

    except XdmaDdr3Error as exc:
        print(f"ERROR: {exc}", file=sys.stderr)
        return 1

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
