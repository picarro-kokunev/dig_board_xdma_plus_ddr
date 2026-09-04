#!/usr/bin/env python3
# access_fpga.py
"""
Host-side tool for the dig_board_blink design_1 block design.

Hardware summary (design_1.bd)
------------------------------
JTAG AXI master: jtag_axi_0 -> axi_smc -> PL peripherals (xsdb JTAG2AXI target).

Register access (via JTAG memory read/write)
    offset 0x0000: axi_gpio_0 (1-bit output -> board led_green_0)
    offset 0x0400: axi_iic_0 (I2C master -> board EEPROM M24M01 on iic_rtl_0)

Board status LEDs
  led_green_0  Host-controllable via axi_gpio_0 bit[0] (JTAG AXI @ 0x0)
  led_red_0    Free-running counter bit[24] (not host-controllable)

This design has no XDMA/ADC streaming path. Use dig_board_pcie_plus_adc for
loopback/print/plot ADC commands over PCIe.

Prerequisites
-------------
Source the Xilinx Python environment before running, for example:
  source /opt/Xilinx/2025.2/Vitis/cli/examples/customer_python_utils/setup_vitis_env.sh

Ensure hw_server is running and the FPGA is programmed with design_1.

Subcommands
-----------
  led        Read or drive led_green_0 through axi_gpio_0
  i2c        Dump axi_iic_0 status registers (debug)
  eeprom     Read or write the on-board M24M01 I2C EEPROM via axi_iic_0

Examples
--------
  python3 access_fpga.py led on
  python3 access_fpga.py led read
  python3 access_fpga.py eeprom read --offset 0 --length 16
  python3 access_fpga.py eeprom write --offset 0 --data 48656c6c6f
"""

import argparse
import sys
import time

try:
    import xsdb
except ImportError as exc:
    xsdb = None
    _XSDB_IMPORT_ERROR = exc
else:
    _XSDB_IMPORT_ERROR = None

# --- PL register map (must match design_1 Address Editor / jtag_axi_0 Data) ---
GPIO_BASE = 0x0000_0000
GPIO_DATA_OFFSET = 0x00
GPIO_LED_BIT = 0

# axi_iic_0 @ 0x400 (M24M01 EEPROM on iic_rtl_0, see io.xdc)
IIC_BASE = 0x0000_0400
IIC_CR = 0x100
IIC_SR = 0x104
IIC_ISR = 0x020
IIC_TX_FIFO = 0x108
IIC_RX_FIFO = 0x10C
IIC_RX_FIFO_PIRQ = 0x120

IIC_CR_EN = 0x01
IIC_CR_TX_FIFO_RESET = 0x02
IIC_CR_MSMS = 0x04

IIC_SR_BB = 0x04
IIC_SR_RX_FIFO_EMPTY = 0x40
IIC_SR_TX_FIFO_EMPTY = 0x80

IIC_TX_FIFO_START = 1 << 8
IIC_TX_FIFO_STOP = 1 << 9

# Dynamic master receive byte count is limited to 8 bits in TX_FIFO[7:0].
IIC_MAX_READ_BYTES = 255

# M24M01: 1 Mbit (128 KiB), 17-bit address, 256-byte page writes
EEPROM_SLAVE_ADDR = 0x50
EEPROM_SIZE_BYTES = 128 * 1024
EEPROM_PAGE_SIZE = 256
EEPROM_WRITE_CYCLE_S = 0.005
IIC_TIMEOUT_S = 1.0

DEFAULT_JTAG_TARGET_FILTER = "name =~ JTAG2AXI"


class JtagAxiBar:
    """32-bit AXI register access through xsdb JTAG2AXI memory commands."""

    def __init__(self, target_filter=DEFAULT_JTAG_TARGET_FILTER):
        if xsdb is None:
            raise ImportError(
                "xsdb is not available; source the Xilinx Vitis Python "
                "environment before running this script"
            ) from _XSDB_IMPORT_ERROR
        self._target_filter = target_filter
        self.session = None

    def connect(self):
        self.session = xsdb.start_debug_session()
        self.session.connect()
        self.session.targets("--set", filter=self._target_filter)
        return self

    def close(self):
        self.session = None

    def __enter__(self):
        self.connect()
        return self

    def __exit__(self, *exc):
        self.close()

    def read_u32(self, offset):
        words = self.session.mrd(offset, "-v", size=1, word_size=4)
        if isinstance(words, list):
            return int(words[0]) & 0xFFFFFFFF
        return int(words) & 0xFFFFFFFF

    def write_u32(self, offset, value):
        self.session.mwr(
            offset,
            size=1,
            words=[int(value) & 0xFFFFFFFF],
            word_size=4,
        )

    def gpio_data(self):
        return self.read_u32(GPIO_BASE + GPIO_DATA_OFFSET)

    def set_gpio_led(self, on):
        """Drive led_green_0 (axi_gpio_0 bit[0], active-high output)."""
        addr = GPIO_BASE + GPIO_DATA_OFFSET
        value = self.read_u32(addr)
        if on:
            value |= 1 << GPIO_LED_BIT
        else:
            value &= ~(1 << GPIO_LED_BIT)
        self.write_u32(addr, value)


class AxiIic:
    """Driver for Xilinx axi_iic using PG090 Dynamic Controller Logic Flow."""

    def __init__(self, bar, base=IIC_BASE):
        self._bar = bar
        self._base = base
        self._initialized = False

    def _reg(self, offset):
        return self._base + offset

    def _read_cr(self):
        return self._bar.read_u32(self._reg(IIC_CR))

    def _read_isr(self):
        return self._bar.read_u32(self._reg(IIC_ISR))

    def _write_cr(self, value):
        self._bar.write_u32(self._reg(IIC_CR), value)

    def _read_sr(self):
        return self._bar.read_u32(self._reg(IIC_SR))

    def _tx_fifo(self, value):
        self._bar.write_u32(self._reg(IIC_TX_FIFO), value)

    def _rx_fifo(self):
        return self._bar.read_u32(self._reg(IIC_RX_FIFO)) & 0xFF

    @staticmethod
    def _sr_ready(sr):
        return (
            not (sr & IIC_SR_BB)
            and (sr & IIC_SR_TX_FIFO_EMPTY)
            and (sr & IIC_SR_RX_FIFO_EMPTY)
        )

    @staticmethod
    def _describe_sr(sr):
        parts = []
        if sr & IIC_SR_BB:
            parts.append("BB(bus busy)")
        if not (sr & IIC_SR_TX_FIFO_EMPTY):
            parts.append("TX_FIFO not empty")
        if not (sr & IIC_SR_RX_FIFO_EMPTY):
            parts.append("RX_FIFO not empty")
        if not parts:
            parts.append("ready")
        return f"SR=0x{sr:02x} [{', '.join(parts)}]"

    def _wait_bus_ready(self, timeout=IIC_TIMEOUT_S):
        """Wait until bus is idle and both FIFOs are empty (PG090 pre-transfer check)."""
        deadline = time.monotonic() + timeout
        last_sr = 0
        while time.monotonic() < deadline:
            last_sr = self._read_sr()
            if self._sr_ready(last_sr):
                return
            time.sleep(50e-6)
        raise TimeoutError(
            "I2C bus/FIFOs not ready: "
            f"{self._describe_sr(last_sr)} CR=0x{self._read_cr():02x} "
            f"ISR=0x{self._read_isr():02x}"
        )

    def _drain_rx_fifo(self):
        while not (self._read_sr() & IIC_SR_RX_FIFO_EMPTY):
            self._rx_fifo()

    def _recover_controller(self):
        """
        Clear a stuck master session left by an aborted transfer.

        PG090: clearing CR.MSMS generates STOP and releases the bus.
        """
        self._write_cr(0)
        time.sleep(10e-6)
        self._write_cr(IIC_CR_EN | IIC_CR_TX_FIFO_RESET)
        self._write_cr(IIC_CR_EN)
        self._drain_rx_fifo()
        if self._read_cr() & IIC_CR_MSMS:
            self._write_cr(IIC_CR_EN)
        time.sleep(10e-6)

    def _wait_bus_idle(self, timeout=IIC_TIMEOUT_S):
        deadline = time.monotonic() + timeout
        last_sr = 0
        while time.monotonic() < deadline:
            last_sr = self._read_sr()
            if not (last_sr & IIC_SR_BB) and (last_sr & IIC_SR_TX_FIFO_EMPTY):
                return
            time.sleep(50e-6)
        raise TimeoutError(
            "I2C bus did not become idle: "
            f"{self._describe_sr(last_sr)} CR=0x{self._read_cr():02x}"
        )

    def _wait_rx_not_empty(self, timeout=IIC_TIMEOUT_S):
        deadline = time.monotonic() + timeout
        while time.monotonic() < deadline:
            if not (self._read_sr() & IIC_SR_RX_FIFO_EMPTY):
                return
            time.sleep(50e-6)
        raise TimeoutError("I2C receive timeout")

    def _prepare(self):
        """
        PG090 Dynamic Controller initialization / pre-transfer setup:
          1. RX_FIFO_PIRQ = 0x0F (once)
          2. Reset TX FIFO
          3. Enable controller (EN=1), release TX FIFO reset
          4. Check FIFOs empty and bus not busy (after EN=1)
        """
        if not self._initialized:
            self._bar.write_u32(self._reg(IIC_RX_FIFO_PIRQ), 0x0F)
            self._initialized = True

        self._write_cr(IIC_CR_EN | IIC_CR_TX_FIFO_RESET)
        self._write_cr(IIC_CR_EN)
        time.sleep(10e-6)

        if not self._sr_ready(self._read_sr()):
            self._recover_controller()

        self._wait_bus_ready()

    @staticmethod
    def _i2c_addr_byte(slave_7bit, read=False):
        addr = (slave_7bit << 1) & 0xFE
        if read:
            addr |= 0x01
        return addr & 0xFF

    def _write_payload(self, payload):
        """
        PG090 dynamic master write:
          START + first byte, middle bytes plain, STOP + last byte.
        """
        if not payload:
            raise ValueError("I2C write payload is empty")
        self._prepare()
        self._tx_fifo(IIC_TX_FIFO_START | (payload[0] & 0xFF))
        for byte_val in payload[1:-1]:
            self._tx_fifo(byte_val & 0xFF)
        self._tx_fifo(IIC_TX_FIFO_STOP | (payload[-1] & 0xFF))
        self._wait_bus_idle()

    def write(self, slave_7bit, mem_addr, data):
        addr_hi = (mem_addr >> 8) & 0xFF
        addr_lo = mem_addr & 0xFF
        payload = [self._i2c_addr_byte(slave_7bit, read=False), addr_hi, addr_lo]
        payload.extend(data)
        self._write_payload(payload)

    def read(self, slave_7bit, mem_addr, length):
        """
        PG090 EEPROM random-read sequence (dynamic mode):
          1. START + write address
          2. EEPROM internal address byte(s)
          3. START + read address (repeated start when MSMS=1)
          4. STOP + receive byte count
          5. Read RX FIFO until count bytes received
        """
        if length <= 0:
            return b""
        if length > IIC_MAX_READ_BYTES:
            raise ValueError(
                f"I2C read length {length} exceeds dynamic-mode limit "
                f"of {IIC_MAX_READ_BYTES} bytes per transfer"
            )

        write_addr = self._i2c_addr_byte(slave_7bit, read=False)
        read_addr = self._i2c_addr_byte(slave_7bit, read=True)
        addr_hi = (mem_addr >> 8) & 0xFF
        addr_lo = mem_addr & 0xFF

        self._prepare()
        self._tx_fifo(IIC_TX_FIFO_START | write_addr)
        self._tx_fifo(addr_hi)
        self._tx_fifo(addr_lo)
        self._tx_fifo(IIC_TX_FIFO_START | read_addr)
        self._tx_fifo(IIC_TX_FIFO_STOP | (length & 0xFF))

        out = bytearray()
        for _ in range(length):
            self._wait_rx_not_empty()
            out.append(self._rx_fifo())
        self._wait_bus_idle()
        return bytes(out)


class M24M01Eeprom:
    """M24M01 (128 KiB) EEPROM on the board I2C bus."""

    def __init__(self, iic, slave_addr=EEPROM_SLAVE_ADDR):
        self._iic = iic
        self._base_slave = slave_addr & 0xFE

    def read(self, offset, length):
        self._check_range(offset, length)
        out = bytearray()
        pos = 0
        while pos < length:
            slave, mem_addr = self._resolve_offset(offset + pos)
            chunk = min(length - pos, 0x10000 - mem_addr, IIC_MAX_READ_BYTES)
            out.extend(self._iic.read(slave, mem_addr, chunk))
            pos += chunk
        return bytes(out)

    def write(self, offset, data):
        self._check_range(offset, len(data))
        pos = 0
        while pos < len(data):
            slave, mem_addr = self._resolve_offset(offset + pos)
            bank_remaining = 0x10000 - mem_addr
            page_off = mem_addr & (EEPROM_PAGE_SIZE - 1)
            chunk = min(len(data) - pos, EEPROM_PAGE_SIZE - page_off, bank_remaining)
            self._iic.write(slave, mem_addr, data[pos:pos + chunk])
            pos += chunk
            time.sleep(EEPROM_WRITE_CYCLE_S)

    def _resolve_offset(self, offset):
        a16 = (offset >> 16) & 1
        slave = self._base_slave | a16
        mem_addr = offset & 0xFFFF
        return slave, mem_addr

    @staticmethod
    def _check_range(offset, length):
        if offset < 0 or length < 0:
            raise ValueError("offset and length must be non-negative")
        if offset + length > EEPROM_SIZE_BYTES:
            raise ValueError(
                f"EEPROM range 0x{offset:x}+0x{length:x} exceeds "
                f"0x{EEPROM_SIZE_BYTES:x} bytes"
            )


def parse_hex_bytes(value):
    text = value.strip().lower()
    if text.startswith("0x"):
        text = text[2:]
    text = "".join(text.split())
    if not text:
        raise argparse.ArgumentTypeError("empty hex data")
    if len(text) % 2:
        raise argparse.ArgumentTypeError("hex data must have an even number of digits")
    try:
        return bytes.fromhex(text)
    except ValueError as exc:
        raise argparse.ArgumentTypeError(f"invalid hex data: {exc}") from exc


def format_hex_dump(data, base_offset=0, bytes_per_line=16):
    lines = []
    for start in range(0, len(data), bytes_per_line):
        chunk = data[start:start + bytes_per_line]
        hex_part = " ".join(f"{b:02x}" for b in chunk)
        ascii_part = "".join(chr(b) if 32 <= b < 127 else "." for b in chunk)
        lines.append(
            f"{base_offset + start:08x}  {hex_part:<{bytes_per_line * 3 - 1}}  {ascii_part}"
        )
    return "\n".join(lines)


def cmd_led(args):
    with JtagAxiBar(args.jtag_target) as bar:
        gpio_addr = GPIO_BASE + GPIO_DATA_OFFSET

        if args.led_cmd == "read":
            data = bar.gpio_data()
            on = bool(data & (1 << GPIO_LED_BIT))
            print(
                f"JTAG AXI: GPIO_DATA @ 0x{gpio_addr:04x} = 0x{data:08x} "
                f"-> led_green_0 {'ON' if on else 'OFF'}"
            )
            return 0

        if args.led_cmd == "on":
            bar.set_gpio_led(True)
            state = "ON"
        elif args.led_cmd == "off":
            bar.set_gpio_led(False)
            state = "OFF"
        else:
            data = bar.gpio_data()
            new_on = not bool(data & (1 << GPIO_LED_BIT))
            bar.set_gpio_led(new_on)
            state = "ON" if new_on else "OFF"

        print(f"JTAG AXI: led_green_0 -> {state}")
    return 0


def cmd_i2c(args):
    with JtagAxiBar(args.jtag_target) as bar:
        iic = AxiIic(bar)

        def dump_state(label):
            cr = iic._read_cr()
            sr = iic._read_sr()
            isr = iic._read_isr()
            print(f"{label}")
            print(f"  CR  @ 0x{iic._reg(IIC_CR):04x} = 0x{cr:08x}  EN={bool(cr & IIC_CR_EN)} "
                  f"MSMS={bool(cr & IIC_CR_MSMS)} TX_RST={bool(cr & IIC_CR_TX_FIFO_RESET)}")
            print(f"  SR  @ 0x{iic._reg(IIC_SR):04x} = 0x{sr:08x}  {AxiIic._describe_sr(sr)}")
            print(f"  ISR @ 0x{iic._reg(IIC_ISR):04x} = 0x{isr:08x}")

        print(f"axi_iic_0 @ 0x{IIC_BASE:04x} (JTAG AXI register window)")
        dump_state("before init:")
        iic._prepare()
        dump_state("after init:")
        print(f"  RX_FIFO_PIRQ @ 0x{iic._reg(IIC_RX_FIFO_PIRQ):04x} = "
              f"0x{bar.read_u32(iic._reg(IIC_RX_FIFO_PIRQ)):08x}")
    return 0


def cmd_eeprom(args):
    with JtagAxiBar(args.jtag_target) as bar:
        eeprom = M24M01Eeprom(AxiIic(bar), slave_addr=args.slave_addr)

        if args.eeprom_cmd == "read":
            data = eeprom.read(args.offset, args.length)
            slave, _ = eeprom._resolve_offset(args.offset)
            print(
                f"JTAG AXI: EEPROM read @ 0x{args.offset:05x} "
                f"({len(data)} bytes, slave=0x{slave:02x})"
            )
            print(format_hex_dump(data, base_offset=args.offset))
            return 0

        if args.data is not None and args.file is not None:
            raise ValueError("use only one of --data or --file")

        if args.data is not None:
            payload = args.data
        elif args.file is not None:
            with open(args.file, "rb") as fh:
                payload = fh.read()
        else:
            raise ValueError("eeprom write requires --data or --file")

        eeprom.write(args.offset, payload)
        slave, _ = eeprom._resolve_offset(args.offset)
        print(
            f"JTAG AXI: EEPROM wrote {len(payload)} byte(s) "
            f"@ 0x{args.offset:05x} (slave=0x{slave:02x})"
        )
    return 0


def build_parser():
    parser = argparse.ArgumentParser(
        description="Access dig_board_blink PL registers over JTAG AXI (xsdb).",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__,
    )
    parser.add_argument(
        "--jtag-target",
        default=DEFAULT_JTAG_TARGET_FILTER,
        help=f"xsdb target filter for JTAG2AXI (default: {DEFAULT_JTAG_TARGET_FILTER!r})",
    )
    sub = parser.add_subparsers(dest="command", required=True)

    p_led = sub.add_parser(
        "led",
        help="Read or drive led_green_0 via axi_gpio_0 over JTAG AXI.",
    )
    p_led.add_argument(
        "led_cmd",
        choices=("on", "off", "toggle", "read"),
        help="LED action: on, off, toggle, or read current state",
    )
    p_led.set_defaults(func=cmd_led)

    p_i2c = sub.add_parser(
        "i2c",
        help="Initialize axi_iic_0 and print CR/SR/ISR for debugging.",
    )
    p_i2c.set_defaults(func=cmd_i2c)

    p_eeprom = sub.add_parser(
        "eeprom",
        help="Read or write the on-board M24M01 EEPROM via axi_iic_0.",
    )
    p_eeprom.add_argument(
        "--slave-addr",
        type=lambda x: int(x, 0),
        default=EEPROM_SLAVE_ADDR,
        help=(
            f"Base 7-bit I2C slave address for A16=0 "
            f"(default: 0x{EEPROM_SLAVE_ADDR:02x}; upper 64 KiB uses base|1)"
        ),
    )
    p_eeprom_sub = p_eeprom.add_subparsers(dest="eeprom_cmd", required=True)

    p_eeprom_read = p_eeprom_sub.add_parser(
        "read",
        help="Read bytes from EEPROM and print a hex dump.",
    )
    p_eeprom_read.add_argument(
        "--offset",
        type=lambda x: int(x, 0),
        default=0,
        help="Start EEPROM address (default: 0)",
    )
    p_eeprom_read.add_argument(
        "--length",
        type=int,
        default=16,
        help="Number of bytes to read (default: 16)",
    )
    p_eeprom_read.set_defaults(func=cmd_eeprom)

    p_eeprom_write = p_eeprom_sub.add_parser(
        "write",
        help="Write bytes to EEPROM.",
    )
    p_eeprom_write.add_argument(
        "--offset",
        type=lambda x: int(x, 0),
        default=0,
        help="Start EEPROM address (default: 0)",
    )
    p_eeprom_write.add_argument(
        "--data",
        type=parse_hex_bytes,
        help="Hex payload to write, e.g. 48656c6c6f or 0x48 65 6c 6c 6f",
    )
    p_eeprom_write.add_argument(
        "--file",
        help="Binary file whose contents are written at --offset",
    )
    p_eeprom_write.set_defaults(func=cmd_eeprom)

    return parser


def main(argv=None):
    parser = build_parser()
    args = parser.parse_args(argv)
    if xsdb is None:
        print(
            "xsdb is not available.\n"
            "Hint: source the Xilinx Vitis Python environment, for example:\n"
            "  source /opt/Xilinx/2025.2/Vitis/cli/examples/customer_python_utils/"
            "setup_vitis_env.sh",
            file=sys.stderr,
        )
        return 1
    try:
        return args.func(args)
    except (TimeoutError, OSError, RuntimeError) as exc:
        print(
            f"JTAG/AXI error: {exc}\n"
            "Hint: ensure hw_server is running, the FPGA is programmed with "
            "design_1, and the JTAG2AXI target is visible.",
            file=sys.stderr,
        )
        return 1


if __name__ == "__main__":
    sys.exit(main())
