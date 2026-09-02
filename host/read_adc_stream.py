#!/usr/bin/env python3
"""
Host-side test/capture tool for the dig_board_pcie_plus_adc XDMA design.

Hardware summary (design_1.bd)
------------------------------
PCIe endpoint: Xilinx XDMA 4.2, Gen2 x4, device 10ee:7024, AXI-Stream DMA mode.

Stream DMA (bulk ADC data)
  /dev/xdma<N>_h2c_0, /dev/xdma<N>_c2h_0  -> channel 0 loopback
      (M_AXIS_H2C_0 wired to S_AXIS_C2H_0)

  /dev/xdma<N>_c2h_1                       -> channel 1 ADC stream
      adc_ctrl_0 (50 MHz) -> adc_sample_fifo (FIFO Generator, 2048x16,
      independent clocks, FWFT) -> adc_c2h_axis_bridge -> S_AXIS_C2H_1

Register / GPIO access (PL control)
  /dev/xdma<N>_user                        -> XDMA AXI-Lite master BAR (64 KiB)
      offset 0x0000: axi_gpio_0 (1-bit output -> board led_red_0)

  /dev/xdma<N>_control                     -> XDMA IP internal registers (unused here)

Board status LEDs (not all host-controllable)
  led_green_0  PCIe link up (xdma_0/user_lnk_up, inverted in PL)
  led_red_0    Host-controlled via axi_gpio_0 bit[0] (/dev/xdmaN_user)

ADC packet format (adc_c2h_axis_bridge.v)
-----------------------------------------
  128-bit AXI-Stream beats, 8 samples/beat (16-bit little-endian words).
  TLAST every PKT_BEATS=512 beats ->
      512 * 8 * 2 = 8192 bytes/packet = 4096 samples/packet.

  Each 16-bit sample word (adc_ctrl.v):
    bit[15]    adc_id  (0 = channel A, 1 = channel B)
    bit[14]    adc_ofa (overflow/underflow flag)
    bits[13:0] raw ADC code (unsigned 14-bit)

Subcommands
-----------
  loopback   H2C_0 -> C2H_0 loopback self-test
  print      Decode and print samples from C2H_1
  plot       Live matplotlib plot of C2H_1 samples
  led        Read or drive led_red_0 through axi_gpio_0 (/dev/xdmaN_user)

Examples
--------
  python3 read_adc_stream.py loopback
  python3 read_adc_stream.py print --num-packets 4
  python3 read_adc_stream.py print --adc-ch-list 0
  python3 read_adc_stream.py plot --window-samples 4096 --adc-ch-list 0,1
  python3 read_adc_stream.py led on
  python3 read_adc_stream.py led read
"""

import argparse
import mmap
import os
import struct
import sys
import threading
import time
from collections import deque

import numpy as np

# --- Stream / sample format (must match adc_c2h_axis_bridge.v) ---
AXIS_BYTES_PER_BEAT = 16  # 128-bit AXI-Stream beat width (XDMA)
SAMPLE_BYTES = 2
SAMPLES_PER_BEAT = 8
PKT_BEATS = 512
PACKET_BYTES = PKT_BEATS * SAMPLES_PER_BEAT * SAMPLE_BYTES
SAMPLES_PER_PACKET = PACKET_BYTES // SAMPLE_BYTES

CHANNEL_ID_MASK = 0x8000
OFA_MASK = 0x4000
SAMPLE_MASK = 0x3FFF
DEFAULT_ADC_CH_LIST = [0, 1]
VALID_ADC_CHANNELS = frozenset({0, 1})

# --- PL register map (must match design_1 Address Editor / axi_gpio_0) ---
USER_BAR_BYTES = 64 * 1024
GPIO_BASE = 0x0000_0000
GPIO_DATA_OFFSET = 0x00
GPIO_TRI_OFFSET = 0x04
GPIO_LED_BIT = 0


def default_device(xdma_index, channel, direction):
    """Build a /dev/xdmaN_<dir>_<ch> path, e.g. /dev/xdma0_c2h_1."""
    return f"/dev/xdma{xdma_index}_{direction}_{channel}"


def default_user_device(xdma_index):
    """AXI-Lite user BAR for PL peripherals (axi_gpio_0, etc.)."""
    return f"/dev/xdma{xdma_index}_user"


def read_exact(fd, nbytes):
    """Read exactly nbytes from an already-open fd, handling short reads."""
    buf = bytearray(nbytes)
    view = memoryview(buf)
    got = 0
    while got < nbytes:
        n = os.read(fd, nbytes - got)
        if n is None or len(n) == 0:
            raise EOFError(
                f"device closed/EOF after {got}/{nbytes} bytes "
                "(is the FPGA programmed and streaming?)"
            )
        view[got:got + len(n)] = n
        got += len(n)
    return bytes(buf)


def write_exact(fd, data):
    """Write all bytes of data to an already-open fd."""
    sent = 0
    mv = memoryview(data)
    while sent < len(data):
        n = os.write(fd, mv[sent:])
        if n <= 0:
            raise IOError(f"short write ({sent}/{len(data)} bytes sent)")
        sent += n


def align_down(nbytes, align=AXIS_BYTES_PER_BEAT):
    """Round nbytes down to a multiple of align (required for AXIS DMA)."""
    return nbytes - (nbytes % align)


def loopback_transfer(tx, h2c_path, c2h_path, timeout_s=5.0):
    """
    Exercise H2C_0 -> C2H_0 loopback with concurrent read and write.

    Starts C2H read in a background thread, then writes H2C so the FPGA
    can forward data. Returns (tx, rx).
    """
    if len(tx) % AXIS_BYTES_PER_BEAT:
        raise ValueError(
            f"H2C payload must be a multiple of {AXIS_BYTES_PER_BEAT} bytes"
        )
    nbytes = len(tx)
    err = []
    rx_box = []

    def reader():
        try:
            c2h_fd = os.open(c2h_path, os.O_RDONLY)
            try:
                rx_box.append(read_exact(c2h_fd, nbytes))
            finally:
                os.close(c2h_fd)
        except BaseException as exc:  # noqa: BLE001 — surface to main thread
            err.append(exc)

    t = threading.Thread(target=reader, name="c2h-reader", daemon=True)
    t.start()
    # Give the C2H descriptor a moment to arm before H2C push
    time.sleep(0.05)
    try:
        h2c_fd = os.open(h2c_path, os.O_WRONLY)
        try:
            write_exact(h2c_fd, tx)
        finally:
            os.close(h2c_fd)
    except BaseException:
        t.join(timeout=timeout_s)
        raise
    t.join(timeout=timeout_s + 1.0)
    if err:
        raise err[0]
    if not rx_box:
        raise TimeoutError("C2H reader did not complete")
    return tx, rx_box[0]


class UserBar:
    """Memory-mapped access to /dev/xdmaN_user (XDMA AXI-Lite master window)."""

    def __init__(self, path, size=USER_BAR_BYTES):
        self._fd = os.open(path, os.O_RDWR | os.O_SYNC)
        self._mm = mmap.mmap(self._fd, size, mmap.MAP_SHARED,
                             mmap.PROT_READ | mmap.PROT_WRITE)

    def close(self):
        self._mm.close()
        os.close(self._fd)

    def __enter__(self):
        return self

    def __exit__(self, *exc):
        self.close()

    def read_u32(self, offset):
        return struct.unpack_from("<I", self._mm, offset)[0]

    def write_u32(self, offset, value):
        struct.pack_into("<I", self._mm, offset, value)

    def gpio_data(self):
        return self.read_u32(GPIO_BASE + GPIO_DATA_OFFSET)

    def set_gpio_led(self, on):
        """Drive led_red_0 (axi_gpio_0 bit[0], active-high output)."""
        addr = GPIO_BASE + GPIO_DATA_OFFSET
        value = self.read_u32(addr)
        if on:
            value |= 1 << GPIO_LED_BIT
        else:
            value &= ~(1 << GPIO_LED_BIT)
        self.write_u32(addr, value)


def decode_samples(raw_bytes):
    """Decode a raw byte buffer of 16-bit words into (channel, ofa, value)."""
    words = np.frombuffer(raw_bytes, dtype="<u2")
    channel = ((words & CHANNEL_ID_MASK) >> 15).astype(np.uint8)
    ofa = ((words & OFA_MASK) >> 14).astype(np.uint8)
    value = (words & SAMPLE_MASK).astype(np.uint16)
    return channel, ofa, value


def parse_adc_ch_list(value):
    """Parse comma-separated ADC channel ids for argparse (0=A, 1=B)."""
    if isinstance(value, list):
        ch_list = [int(ch) for ch in value]
    else:
        ch_list = [int(part.strip()) for part in str(value).split(",") if part.strip()]
    if not ch_list:
        raise argparse.ArgumentTypeError("adc_ch_list must list at least one channel")
    invalid = [ch for ch in ch_list if ch not in VALID_ADC_CHANNELS]
    if invalid:
        raise argparse.ArgumentTypeError(
            f"invalid adc channel id(s) {invalid}; valid values are 0 (A) and 1 (B)"
        )
    return ch_list


def channel_name(ch_id):
    return "A" if ch_id == 0 else "B"


def filter_samples_by_channels(channel, ofa, value, adc_ch_list):
    """Keep only samples whose adc_id is listed in adc_ch_list."""
    mask = np.isin(channel, np.asarray(adc_ch_list, dtype=channel.dtype))
    return channel[mask], ofa[mask], value[mask]


# ---------------------------------------------------------------------------
# Subcommand: loopback
# ---------------------------------------------------------------------------

def cmd_loopback(args):
    h2c_path = args.h2c or default_device(args.xdma_index, 0, "h2c")
    c2h_path = args.c2h or default_device(args.xdma_index, 0, "c2h")
    size = align_down(args.size)
    if size <= 0:
        raise ValueError(f"size must be >= {AXIS_BYTES_PER_BEAT}")
    if size != args.size:
        print(f"Note: size rounded down to {size} bytes "
              f"(multiple of {AXIS_BYTES_PER_BEAT})")

    print(f"Loopback test: write {size} bytes to {h2c_path}, "
          f"read {size} bytes back from {c2h_path} (concurrent threads)")

    ok_count = 0
    fail_count = 0
    for i in range(args.iterations):
        pattern = np.frombuffer(
            struct.pack("<I", i) * (size // 4 + 1), dtype=np.uint8
        )[:size].copy()
        pattern ^= np.arange(size, dtype=np.uint8)
        tx = pattern.tobytes()

        try:
            _, readback = loopback_transfer(
                tx, h2c_path, c2h_path, timeout_s=args.timeout
            )
        except (EOFError, TimeoutError, OSError) as exc:
            fail_count += 1
            print(f"  iter {i}: FAIL ({exc})")
            continue

        if readback == tx:
            ok_count += 1
            print(f"  iter {i}: PASS ({size} bytes match)")
        else:
            fail_count += 1
            mismatch_at = next(
                (j for j in range(size) if readback[j] != pattern[j]), None
            )
            print(f"  iter {i}: FAIL (first mismatch at byte {mismatch_at})")

    print(f"Loopback result: {ok_count} pass / {fail_count} fail "
          f"out of {args.iterations} iterations")
    return 0 if fail_count == 0 else 1


# ---------------------------------------------------------------------------
# Subcommand: print
# ---------------------------------------------------------------------------

def cmd_print(args):
    c2h_path = args.c2h or default_device(args.xdma_index, 1, "c2h")
    packet_bytes = args.packet_bytes
    ch_names = ",".join(channel_name(ch) for ch in args.adc_ch_list)

    print(f"Reading ADC samples from {c2h_path} "
          f"({packet_bytes} bytes/packet = "
          f"{packet_bytes // SAMPLE_BYTES} samples/packet, "
          f"channels={ch_names})")

    fd = os.open(c2h_path, os.O_RDONLY)
    total_samples = 0
    packets_read = 0
    try:
        while args.num_packets == 0 or packets_read < args.num_packets:
            raw = read_exact(fd, packet_bytes)
            channel, ofa, value = decode_samples(raw)
            channel, ofa, value = filter_samples_by_channels(
                channel, ofa, value, args.adc_ch_list
            )
            packets_read += 1

            n = len(value) if args.max_print == 0 else min(len(value), args.max_print)
            for k in range(n):
                ch = channel_name(channel[k])
                flag = " OFA" if ofa[k] else ""
                print(f"pkt={packets_read:6d} idx={k:5d} ch={ch} "
                    # print in hex to match the FPGA output
                      f"value=0x{value[k]:04x}{flag}")

            total_samples += len(value)
            if args.max_print == 0:
                print(f"-- packet {packets_read}: {len(value)} samples "
                      f"(total {total_samples}) --")
    except EOFError as e:
        print(f"Stream ended: {e}")
    except KeyboardInterrupt:
        print("\nStopped by user.")
    finally:
        os.close(fd)

    print(f"Read {packets_read} packet(s), {total_samples} sample(s) total.")
    return 0


# ---------------------------------------------------------------------------
# Subcommand: plot
# ---------------------------------------------------------------------------

class StreamReader(threading.Thread):
    """Background reader for C2H_1 ADC packets."""

    def __init__(self, path, packet_bytes, max_queue=8):
        super().__init__(daemon=True)
        self.path = path
        self.packet_bytes = packet_bytes
        self.queue = deque(maxlen=max_queue)
        self.lock = threading.Lock()
        self.stop_event = threading.Event()
        self.error = None

    def run(self):
        try:
            fd = os.open(self.path, os.O_RDONLY)
        except OSError as e:
            self.error = e
            return
        try:
            while not self.stop_event.is_set():
                raw = read_exact(fd, self.packet_bytes)
                decoded = decode_samples(raw)
                with self.lock:
                    self.queue.append(decoded)
        except EOFError as e:
            self.error = e
        finally:
            os.close(fd)

    def pop_all(self):
        with self.lock:
            items = list(self.queue)
            self.queue.clear()
        return items

    def stop(self):
        self.stop_event.set()


def cmd_plot(args):
    import matplotlib.pyplot as plt
    from matplotlib.animation import FuncAnimation

    c2h_path = args.c2h or default_device(args.xdma_index, 1, "c2h")
    window = args.window_samples
    ch_names = ",".join(channel_name(ch) for ch in args.adc_ch_list)

    print(f"Plotting ADC samples from {c2h_path} "
          f"(rolling window: {window} samples/channel, channels={ch_names})")

    reader = StreamReader(c2h_path, args.packet_bytes)
    reader.start()
    time.sleep(0.2)
    if reader.error is not None:
        print(f"Failed to open/read {c2h_path}: {reader.error}", file=sys.stderr)
        return 1

    bufs = {ch: deque(maxlen=window) for ch in args.adc_ch_list}

    fig, ax = plt.subplots()
    lines = {}
    for ch in args.adc_ch_list:
        (lines[ch],) = ax.plot(
            [], [], label=f"Channel {channel_name(ch)}", linewidth=0.8, linestyle="dashed"
        )
    ax.set_xlabel("Sample index (rolling window)")
    ax.set_ylabel("ADC code (unsigned)")
    ax.set_title(f"Live ADC stream: {c2h_path}")
    ax.legend(loc="upper right")
    ax.grid(True, alpha=0.3)

    def update(_frame):
        for channel, _ofa, value in reader.pop_all():
            channel, _ofa, value = filter_samples_by_channels(
                channel, _ofa, value, args.adc_ch_list
            )
            for ch in args.adc_ch_list:
                mask = channel == ch
                bufs[ch].extend(value[mask].tolist())

        plotted = []
        all_vals = []
        max_len = 1
        for ch in args.adc_ch_list:
            if bufs[ch]:
                lines[ch].set_data(range(len(bufs[ch])), list(bufs[ch]))
                plotted.append(lines[ch])
                all_vals.extend(bufs[ch])
                max_len = max(max_len, len(bufs[ch]))

        if all_vals:
            ax.set_xlim(0, max_len)
            lo, hi = min(all_vals), max(all_vals)
            pad = max(1, int(0.05 * (hi - lo + 1)))
            ax.set_ylim(lo - pad, hi + pad)

        if reader.error is not None:
            print(f"\nStream ended: {reader.error}", file=sys.stderr)
            plt.close(fig)

        return plotted

    anim = FuncAnimation(fig, update, interval=args.refresh_ms, blit=False)
    try:
        plt.show()
    finally:
        reader.stop()
    del anim
    return 0


# ---------------------------------------------------------------------------
# Subcommand: led (axi_gpio_0 via /dev/xdmaN_user)
# ---------------------------------------------------------------------------

def cmd_led(args):
    user_path = args.user or default_user_device(args.xdma_index)
    gpio_addr = GPIO_BASE + GPIO_DATA_OFFSET

    with UserBar(user_path) as bar:
        if args.led_cmd == "read":
            data = bar.gpio_data()
            on = bool(data & (1 << GPIO_LED_BIT))
            print(f"{user_path}: GPIO_DATA @ 0x{gpio_addr:04x} = 0x{data:08x} "
                  f"-> led_red_0 {'ON' if on else 'OFF'}")
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

        print(f"{user_path}: led_red_0 -> {state}")
    return 0


# ---------------------------------------------------------------------------
# CLI
# ---------------------------------------------------------------------------

def build_parser():
    parser = argparse.ArgumentParser(
        description="Test and capture ADC data over the XDMA C2H bridge.",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__,
    )
    parser.add_argument(
        "--xdma-index", type=int, default=0,
        help="XDMA device index N in /dev/xdmaN_* (default: 0)",
    )
    adc_parent = argparse.ArgumentParser(add_help=False)
    adc_parent.add_argument(
        "--adc-ch-list", dest="adc_ch_list", type=parse_adc_ch_list,
        default=DEFAULT_ADC_CH_LIST,
        metavar="IDS",
        help="Comma-separated ADC channel ids to display: 0=A, 1=B "
             f"(default: {','.join(str(ch) for ch in DEFAULT_ADC_CH_LIST)})",
    )
    sub = parser.add_subparsers(dest="command", required=True)

    p_loop = sub.add_parser(
        "loopback", help="Test the H2C_0->C2H_0 AXI-Stream loopback stub."
    )
    p_loop.add_argument("--h2c", help="Override H2C channel-0 device path")
    p_loop.add_argument("--c2h", help="Override C2H channel-0 device path")
    p_loop.add_argument(
        "--size", type=int, default=PACKET_BYTES,
        help=f"Bytes per iteration (default: {PACKET_BYTES}, one DMA packet)",
    )
    p_loop.add_argument(
        "--iterations", type=int, default=5,
        help="Number of write/read/compare iterations (default: 5)",
    )
    p_loop.add_argument(
        "--timeout", type=float, default=5.0,
        help="I/O timeout in seconds per iteration (default: 5.0)",
    )
    p_loop.set_defaults(func=cmd_loopback)

    p_print = sub.add_parser(
        "print", help="Print decoded ADC samples from C2H channel 1 to stdout.",
        parents=[adc_parent],
    )
    p_print.add_argument("--c2h", help="Override C2H channel-1 device path")
    p_print.add_argument(
        "--packet-bytes", type=int, default=PACKET_BYTES,
        help=f"Bytes per read() call (default: {PACKET_BYTES}, one DMA packet)",
    )
    p_print.add_argument(
        "--num-packets", type=int, default=1,
        help="Number of packets to read, 0 = read forever (default: 1)",
    )
    p_print.add_argument(
        "--max-print", type=int, default=64,
        help="Max samples to print per packet, 0 = print all (default: 64)",
    )
    p_print.set_defaults(func=cmd_print)

    p_plot = sub.add_parser(
        "plot", help="Live-plot decoded ADC samples from C2H channel 1.",
        parents=[adc_parent],
    )
    p_plot.add_argument("--c2h", help="Override C2H channel-1 device path")
    p_plot.add_argument(
        "--packet-bytes", type=int, default=PACKET_BYTES,
        help=f"Bytes per read() call (default: {PACKET_BYTES}, one DMA packet)",
    )
    p_plot.add_argument(
        "--window-samples", type=int, default=SAMPLES_PER_PACKET,
        help=f"Rolling window size per channel, in samples "
             f"(default: {SAMPLES_PER_PACKET})",
    )
    p_plot.add_argument(
        "--refresh-ms", type=int, default=100,
        help="Plot refresh interval in ms (default: 100)",
    )
    p_plot.set_defaults(func=cmd_plot)

    p_led = sub.add_parser(
        "led",
        help="Read or drive led_red_0 via axi_gpio_0 on /dev/xdmaN_user.",
    )
    p_led.add_argument(
        "--user", help="Override user BAR device path (default: /dev/xdmaN_user)",
    )
    p_led.add_argument(
        "led_cmd", choices=("on", "off", "toggle", "read"),
        help="LED action: on, off, toggle, or read current state",
    )
    p_led.set_defaults(func=cmd_led)

    return parser


def main(argv=None):
    parser = build_parser()
    args = parser.parse_args(argv)
    try:
        return args.func(args)
    except PermissionError as e:
        print(f"Permission denied: {e}\n"
              f"Hint: XDMA device nodes usually require root, or a udev "
              f"rule granting access.", file=sys.stderr)
        return 1
    except FileNotFoundError as e:
        print(f"Device not found: {e}\n"
              f"Hint: check the FPGA is programmed, the xdma driver is "
              f"loaded, and --xdma-index matches your device.",
              file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
