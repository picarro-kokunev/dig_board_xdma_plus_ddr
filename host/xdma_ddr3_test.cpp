// xdma_ddr3_test.cpp
//
// Read/write DDR3 on the dig_board_xdma_plus_ddr design through the Xilinx XDMA driver.
//
// Hardware path (design_1 in project_1/):
//   Host PCIe -> XDMA (M_AXI master) -> axi_smc -> mig_7series_0 (S_AXI) -> DDR3
//
// Address map:
//   AXI offset 0x00000000 .. 0x3FFFFFFF (1 GiB) -> mig_7series_0/memaddr
//
// DDR3 (from mig_b.prj):
//   Device : MT41K256M16XX-107
//   Width  : 32-bit
//   Size   : 1 GiB
//
// Access method:
//   Use the Linux XDMA character devices. lseek() sets the AXI byte address;
//   write() on h2c_* transfers host -> card (DDR write), read() on c2h_* reads
//   card -> host (DDR read).
//
// Requires the Xilinx XDMA kernel module and device nodes, e.g.:
//   /dev/xdma0_h2c_0, /dev/xdma0_c2h_0
//
// Run as root or with read/write permission on those nodes.

#include <algorithm>
#include <chrono>
#include <cctype>
#include <cerrno>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

namespace {

constexpr std::uint64_t kDdr3AxiBase = 0x00000000;
constexpr std::uint64_t kDdr3SizeBytes = 1ULL << 30;  // 1 GiB
constexpr std::size_t kDdr3DataWidthBytes = 4;        // 32-bit DDR interface

constexpr int kDefaultXdmaId = 0;
constexpr int kDefaultH2cChannel = 0;
constexpr int kDefaultC2hChannel = 0;
constexpr std::size_t kDefaultChunkBytes = 1U << 20;  // 1 MiB

class XdmaDdr3Error : public std::runtime_error {
public:
    explicit XdmaDdr3Error(const std::string& message)
        : std::runtime_error(message) {}
};

struct Config {
    int xdma_id = kDefaultXdmaId;
    int h2c_channel = kDefaultH2cChannel;
    int c2h_channel = kDefaultC2hChannel;
    std::size_t chunk_bytes = kDefaultChunkBytes;
};

class XdmaDdr3 {
public:
    explicit XdmaDdr3(const Config& config) : config_(config) {
        h2c_path_ = devicePath("h2c", config.h2c_channel);
        c2h_path_ = devicePath("c2h", config.c2h_channel);
    }

    ~XdmaDdr3() { close(); }

    XdmaDdr3(const XdmaDdr3&) = delete;
    XdmaDdr3& operator=(const XdmaDdr3&) = delete;

    void open() {
        h2c_fd_ = openDevice(h2c_path_, "h2c");
        c2h_fd_ = openDevice(c2h_path_, "c2h");
    }

    void close() {
        if (h2c_fd_ >= 0) {
            ::close(h2c_fd_);
            h2c_fd_ = -1;
        }
        if (c2h_fd_ >= 0) {
            ::close(c2h_fd_);
            c2h_fd_ = -1;
        }
    }

    std::size_t write(std::uint64_t address, const std::vector<std::uint8_t>& data) {
        if (h2c_fd_ < 0) {
            throw XdmaDdr3Error("Device not open");
        }
        if (data.empty()) {
            return 0;
        }

        checkRange(address, data.size());
        if (lseek(h2c_fd_, static_cast<off_t>(address), SEEK_SET) < 0) {
            throw XdmaDdr3Error("H2C lseek failed at 0x" + hex(address) + ": " + std::strerror(errno));
        }

        std::size_t total = 0;
        while (total < data.size()) {
            const std::size_t chunk = std::min(config_.chunk_bytes, data.size() - total);
            const ssize_t written = ::write(h2c_fd_, data.data() + total, chunk);
            if (written <= 0) {
                throw XdmaDdr3Error(
                    "H2C write failed at 0x" + hex(address + total) + " after " + hex(total) + " bytes");
            }
            total += static_cast<std::size_t>(written);
        }
        return total;
    }

    std::vector<std::uint8_t> read(std::uint64_t address, std::size_t length) {
        if (c2h_fd_ < 0) {
            throw XdmaDdr3Error("Device not open");
        }
        if (length == 0) {
            return {};
        }

        checkRange(address, length);
        if (lseek(c2h_fd_, static_cast<off_t>(address), SEEK_SET) < 0) {
            throw XdmaDdr3Error("C2H lseek failed at 0x" + hex(address) + ": " + std::strerror(errno));
        }

        std::vector<std::uint8_t> out;
        out.reserve(length);

        std::size_t total = 0;
        while (total < length) {
            const std::size_t chunk = std::min(config_.chunk_bytes, length - total);
            std::vector<std::uint8_t> buffer(chunk);
            const ssize_t got = ::read(c2h_fd_, buffer.data(), chunk);
            if (got <= 0) {
                throw XdmaDdr3Error(
                    "C2H read failed at 0x" + hex(address + total) + " after " + hex(total) + " bytes");
            }
            out.insert(out.end(), buffer.begin(), buffer.begin() + got);
            total += static_cast<std::size_t>(got);
        }
        return out;
    }

    std::size_t fill(std::uint64_t address, std::size_t length, const std::vector<std::uint8_t>& pattern) {
        if (pattern.empty()) {
            throw XdmaDdr3Error("Pattern must not be empty");
        }
        if (pattern.size() % kDdr3DataWidthBytes != 0) {
            throw XdmaDdr3Error("Pattern length must be 4-byte aligned");
        }

        std::vector<std::uint8_t> block;
        block.reserve(config_.chunk_bytes);
        while (block.size() < config_.chunk_bytes) {
            const std::size_t copy = std::min(pattern.size(), config_.chunk_bytes - block.size());
            block.insert(block.end(), pattern.begin(), pattern.begin() + static_cast<std::ptrdiff_t>(copy));
        }

        std::size_t remaining = length;
        std::uint64_t offset = address;
        std::size_t written = 0;
        while (remaining > 0) {
            std::size_t size = std::min(block.size(), remaining);
            size -= size % kDdr3DataWidthBytes;
            if (size == 0) {
                break;
            }
            write(offset, std::vector<std::uint8_t>(block.begin(), block.begin() + static_cast<std::ptrdiff_t>(size)));
            written += size;
            offset += size;
            remaining -= size;
        }
        return written;
    }

    struct VerifyResult {
        bool ok = false;
        std::size_t mismatch_offset = 0;
        std::uint8_t expected_value = 0;
    };

    VerifyResult verify(std::uint64_t address, const std::vector<std::uint8_t>& expected) {
        const std::vector<std::uint8_t> actual = read(address, expected.size());
        VerifyResult result;
        if (actual == expected) {
            result.ok = true;
            return result;
        }

        const std::size_t limit = std::min(actual.size(), expected.size());
        for (std::size_t index = 0; index < limit; ++index) {
            if (actual[index] != expected[index]) {
                result.ok = false;
                result.mismatch_offset = index;
                result.expected_value = expected[index];
                return result;
            }
        }

        result.ok = false;
        result.mismatch_offset = actual.size();
        result.expected_value = 0;
        return result;
    }

    const std::string& h2cPath() const { return h2c_path_; }
    const std::string& c2hPath() const { return c2h_path_; }

private:
    Config config_;
    std::string h2c_path_;
    std::string c2h_path_;
    int h2c_fd_ = -1;
    int c2h_fd_ = -1;

    std::string devicePath(const char* direction, int channel) const {
        return "/dev/xdma" + std::to_string(config_.xdma_id) + "_" + direction + "_" + std::to_string(channel);
    }

    static std::string hex(std::uint64_t value) {
        std::ostringstream oss;
        oss << std::hex << value;
        return oss.str();
    }

    static int openDevice(const std::string& path, const char* label) {
        if (!std::filesystem::exists(path)) {
            throw XdmaDdr3Error(
                "Missing XDMA " + std::string(label) + " device " + path +
                ". Load the xdma driver and check PCIe enumeration.");
        }

        const int fd = ::open(path.c_str(), O_RDWR);
        if (fd < 0) {
            throw XdmaDdr3Error("Cannot open " + path + ": " + std::strerror(errno));
        }
        return fd;
    }

    static void checkRange(std::uint64_t address, std::size_t length) {
        if (address < kDdr3AxiBase) {
            throw XdmaDdr3Error("Address 0x" + hex(address) + " is below DDR3 base");
        }

        const std::uint64_t end = address + length;
        const std::uint64_t limit = kDdr3AxiBase + kDdr3SizeBytes;
        if (end > limit) {
            throw XdmaDdr3Error(
                "Transfer 0x" + hex(address) + "+0x" + hex(length) + " exceeds DDR3 range [0x" +
                hex(kDdr3AxiBase) + ", 0x" + hex(limit - 1) + "]");
        }
        if (address % kDdr3DataWidthBytes != 0) {
            throw XdmaDdr3Error("Address 0x" + hex(address) + " is not 4-byte aligned");
        }
        if (length % kDdr3DataWidthBytes != 0) {
            throw XdmaDdr3Error("Length 0x" + hex(length) + " is not 4-byte aligned");
        }
    }
};

std::string trim(std::string_view text) {
    std::size_t start = 0;
    while (start < text.size() && std::isspace(static_cast<unsigned char>(text[start])) != 0) {
        ++start;
    }
    std::size_t end = text.size();
    while (end > start && std::isspace(static_cast<unsigned char>(text[end - 1])) != 0) {
        --end;
    }
    return std::string(text.substr(start, end - start));
}

std::uint64_t parseInt(std::string_view text) {
    const std::string cleaned = trim(text);
    if (cleaned.empty()) {
        throw XdmaDdr3Error("Invalid integer: empty value");
    }

    char* end = nullptr;
    errno = 0;
    const unsigned long long value = std::strtoull(cleaned.c_str(), &end, 0);
    if (errno != 0 || end == cleaned.c_str() || *end != '\0') {
        throw XdmaDdr3Error("Invalid integer: " + cleaned);
    }
    return static_cast<std::uint64_t>(value);
}

std::vector<std::uint8_t> parseHexBytes(std::string_view text) {
    std::string cleaned;
    cleaned.reserve(text.size());
    for (char ch : text) {
        if (ch == '_' || ch == ' ' || ch == '\t') {
            continue;
        }
        cleaned.push_back(ch);
    }

    std::string digits;
    digits.reserve(cleaned.size());
    for (std::size_t i = 0; i < cleaned.size(); ++i) {
        if (i + 1 < cleaned.size() && cleaned[i] == '0' &&
            (cleaned[i + 1] == 'x' || cleaned[i + 1] == 'X')) {
            i += 1;
            continue;
        }
        if (cleaned[i] == 'x' || cleaned[i] == 'X') {
            continue;
        }
        digits.push_back(cleaned[i]);
    }

    if (digits.empty()) {
        return {};
    }
    if (digits.size() % 2 != 0) {
        digits.insert(digits.begin(), '0');
    }

    std::vector<std::uint8_t> out;
    out.reserve(digits.size() / 2);
    for (std::size_t i = 0; i < digits.size(); i += 2) {
        const std::string byte_str = digits.substr(i, 2);
        char* end = nullptr;
        errno = 0;
        const unsigned long value = std::strtoul(byte_str.c_str(), &end, 16);
        if (errno != 0 || end != byte_str.c_str() + 2) {
            throw XdmaDdr3Error("Invalid hex byte pair: " + byte_str);
        }
        out.push_back(static_cast<std::uint8_t>(value));
    }
    return out;
}

std::vector<std::uint8_t> readBinaryFile(const std::string& path) {
    std::ifstream input(path, std::ios::binary);
    if (!input) {
        throw XdmaDdr3Error("Cannot read file " + path + ": " + std::strerror(errno));
    }
    return std::vector<std::uint8_t>((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
}

void writeBinaryFile(const std::string& path, const std::vector<std::uint8_t>& data) {
    std::ofstream output(path, std::ios::binary);
    if (!output) {
        throw XdmaDdr3Error("Cannot write file " + path + ": " + std::strerror(errno));
    }
    output.write(reinterpret_cast<const char*>(data.data()), static_cast<std::streamsize>(data.size()));
    if (!output) {
        throw XdmaDdr3Error("Failed to write file " + path);
    }
}

std::string formatHexDump(const std::vector<std::uint8_t>& data, std::uint64_t base_address = 0, std::size_t width = 16) {
    std::ostringstream out;
    for (std::size_t offset = 0; offset < data.size(); offset += width) {
        out << std::hex << std::setw(8) << std::setfill('0') << (base_address + offset) << "  ";

        const std::size_t chunk_len = std::min(width, data.size() - offset);
        for (std::size_t i = 0; i < width; ++i) {
            if (i < chunk_len) {
                out << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[offset + i]) << ' ';
            } else {
                out << "   ";
            }
        }

        out << ' ';
        for (std::size_t i = 0; i < chunk_len; ++i) {
            const unsigned char byte = data[offset + i];
            out << (byte >= 32 && byte < 127 ? static_cast<char>(byte) : '.');
        }
        out << '\n';
    }
    return out.str();
}

std::vector<std::uint8_t> incrementalPattern(std::size_t length, std::uint8_t seed = 0) {
    std::vector<std::uint8_t> out(length);
    for (std::size_t index = 0; index < length; ++index) {
        out[index] = static_cast<std::uint8_t>((seed + index) & 0xFF);
    }
    return out;
}

std::vector<std::uint8_t> walkingOnesPattern(std::size_t length) {
    std::vector<std::uint8_t> out(length, 0);
    for (std::size_t index = 0; index < length; index += kDdr3DataWidthBytes) {
        const std::uint32_t word_index = static_cast<std::uint32_t>(index / kDdr3DataWidthBytes);
        const std::uint32_t value = 1U << (word_index % 32U);
        out[index + 0] = static_cast<std::uint8_t>(value & 0xFF);
        out[index + 1] = static_cast<std::uint8_t>((value >> 8) & 0xFF);
        out[index + 2] = static_cast<std::uint8_t>((value >> 16) & 0xFF);
        out[index + 3] = static_cast<std::uint8_t>((value >> 24) & 0xFF);
    }
    return out;
}

std::vector<std::uint8_t> aa55Pattern(std::size_t length) {
    std::vector<std::uint8_t> out(length);
    for (std::size_t index = 0; index < length; index += kDdr3DataWidthBytes) {
        out[index + 0] = 0xAA;
        out[index + 1] = 0x55;
        out[index + 2] = 0x00;
        out[index + 3] = 0x00;
    }
    return out;
}

void runSelfTest(XdmaDdr3& ddr, std::uint64_t offset, std::size_t size) {
    std::cout << "Self-test: offset=0x" << std::hex << offset << ", size=0x" << size << std::dec << '\n';

    struct PatternCase {
        const char* name;
        std::vector<std::uint8_t> data;
    };

    const std::vector<PatternCase> patterns = {
        {"incremental", incrementalPattern(size, 0xA5)},
        {"walking-ones", walkingOnesPattern(size)},
        {"aa55", aa55Pattern(size)},
    };

    for (const PatternCase& pattern : patterns) {
        std::cout << "  pattern " << pattern.name << ": write..." << std::flush;
        ddr.write(offset, pattern.data);
        std::cout << " read/verify..." << std::flush;

        const XdmaDdr3::VerifyResult result = ddr.verify(offset, pattern.data);
        if (result.ok) {
            std::cout << " PASS\n";
            continue;
        }

        std::ostringstream err;
        err << "Pattern " << pattern.name << " failed at +0x" << std::hex << result.mismatch_offset
            << ", expected 0x" << std::setw(2) << std::setfill('0') << static_cast<int>(result.expected_value);
        throw XdmaDdr3Error(err.str());
    }

    std::cout << "Self-test PASSED\n";
}

void runBandwidthTest(XdmaDdr3& ddr, std::uint64_t offset, std::size_t size, int iterations) {
    const std::vector<std::uint8_t> payload = incrementalPattern(size, 0x5A);
    std::cout << "Bandwidth test: offset=0x" << std::hex << offset << ", size=0x" << size << std::dec
              << ", iterations=" << iterations << '\n';

    const auto write_start = std::chrono::steady_clock::now();
    for (int i = 0; i < iterations; ++i) {
        ddr.write(offset, payload);
    }
    const auto write_end = std::chrono::steady_clock::now();

    const auto read_start = std::chrono::steady_clock::now();
    for (int i = 0; i < iterations; ++i) {
        const std::vector<std::uint8_t> data = ddr.read(offset, size);
        if (data != payload) {
            throw XdmaDdr3Error("Readback mismatch during bandwidth test");
        }
    }
    const auto read_end = std::chrono::steady_clock::now();

    const double write_elapsed =
        std::chrono::duration<double>(write_end - write_start).count();
    const double read_elapsed =
        std::chrono::duration<double>(read_end - read_start).count();

    const double write_mbps = (static_cast<double>(size) * iterations / write_elapsed) / (1024.0 * 1024.0);
    const double read_mbps = (static_cast<double>(size) * iterations / read_elapsed) / (1024.0 * 1024.0);

    std::cout << std::fixed << std::setprecision(1);
    std::cout << "  write: " << write_mbps << " MiB/s (" << std::setprecision(3) << write_elapsed << " s total)\n";
    std::cout << "  read : " << read_mbps << " MiB/s (" << read_elapsed << " s total)\n";
}

void printUsage(const char* prog) {
    std::cout <<
        "Usage: " << prog << " [options] <command> [command args]\n"
        "\n"
        "Global options:\n"
        "  --xdma-id N         XDMA device index (default: 0)\n"
        "  --h2c-channel N     H2C DMA channel for writes (default: 0)\n"
        "  --c2h-channel N     C2H DMA channel for reads (default: 0)\n"
        "  --chunk-bytes N     Max bytes per DMA syscall (default: 1048576)\n"
        "\n"
        "Commands:\n"
        "  read --offset ADDR --length LEN [--out FILE]\n"
        "  write --offset ADDR (--hex HEX | --file FILE)\n"
        "  fill --offset ADDR --length LEN [--pattern HEX]\n"
        "  verify --offset ADDR (--hex HEX | --file FILE)\n"
        "  test\n"
        "  bench [--offset ADDR] [--size BYTES] [--iterations N]\n"
        "  info [--list-devices]\n";
}

struct Args {
    Config config;
    std::string command;
    std::vector<std::string> positional;
};

Args parseArgs(int argc, char* argv[]) {
    Args args;
    int index = 1;
    while (index < argc) {
        const std::string token = argv[index];
        if (token == "--xdma-id") {
            if (++index >= argc) {
                throw XdmaDdr3Error("--xdma-id requires a value");
            }
            args.config.xdma_id = static_cast<int>(parseInt(argv[index++]));
            continue;
        }
        if (token == "--h2c-channel") {
            if (++index >= argc) {
                throw XdmaDdr3Error("--h2c-channel requires a value");
            }
            args.config.h2c_channel = static_cast<int>(parseInt(argv[index++]));
            continue;
        }
        if (token == "--c2h-channel") {
            if (++index >= argc) {
                throw XdmaDdr3Error("--c2h-channel requires a value");
            }
            args.config.c2h_channel = static_cast<int>(parseInt(argv[index++]));
            continue;
        }
        if (token == "--chunk-bytes") {
            if (++index >= argc) {
                throw XdmaDdr3Error("--chunk-bytes requires a value");
            }
            args.config.chunk_bytes = static_cast<std::size_t>(parseInt(argv[index++]));
            continue;
        }
        if (token.rfind("--", 0) == 0) {
            args.positional.push_back(token);
            ++index;
            continue;
        }
        args.command = token;
        ++index;
        while (index < argc) {
            args.positional.push_back(argv[index++]);
        }
        break;
    }

    if (args.command.empty()) {
        throw XdmaDdr3Error("Missing command");
    }
    return args;
}

std::string getOption(const std::vector<std::string>& args, const std::string& name) {
    for (std::size_t i = 0; i + 1 < args.size(); ++i) {
        if (args[i] == name) {
            return args[i + 1];
        }
    }
    return {};
}

bool hasFlag(const std::vector<std::string>& args, const std::string& name) {
    return std::find(args.begin(), args.end(), name) != args.end();
}

int cmdInfo(const Config& config, const std::vector<std::string>& args) {
    std::cout << "design_1 DDR3 map\n";
    std::cout << "  AXI base : 0x" << std::hex << std::setw(8) << std::setfill('0') << kDdr3AxiBase << std::dec
              << '\n';
    std::cout << "  Size     : 0x" << std::hex << kDdr3SizeBytes << std::dec << " ("
              << (kDdr3SizeBytes / (1024 * 1024)) << " MiB)\n";
    std::cout << "  Width    : " << (kDdr3DataWidthBytes * 8) << "-bit\n";
    std::cout << "  Path     : XDMA M_AXI -> axi_smc -> mig_7series_0 S_AXI\n";
    std::cout << "  Devices  : /dev/xdma" << config.xdma_id << "_h2c_" << config.h2c_channel << ", /dev/xdma"
              << config.xdma_id << "_c2h_" << config.c2h_channel << '\n';

    if (hasFlag(args, "--list-devices")) {
        std::vector<std::string> nodes;
        for (const auto& entry : std::filesystem::directory_iterator("/dev")) {
            const std::string name = entry.path().filename().string();
            if (name.rfind("xdma", 0) == 0) {
                nodes.push_back(entry.path().string());
            }
        }
        std::sort(nodes.begin(), nodes.end());

        if (!nodes.empty()) {
            std::cout << "\nDetected nodes:\n";
            for (const std::string& node : nodes) {
                std::cout << "  " << node << '\n';
            }
        } else {
            std::cout << "\nNo /dev/xdma* nodes found.\n";
        }
    }
    return 0;
}

}  // namespace

int main(int argc, char* argv[]) {
    try {
        const Args args = parseArgs(argc, argv);

        if (args.command == "info") {
            return cmdInfo(args.config, args.positional);
        }

        XdmaDdr3 ddr(args.config);
        ddr.open();

        if (args.command == "read") {
            const std::uint64_t offset = parseInt(getOption(args.positional, "--offset"));
            const std::size_t length = static_cast<std::size_t>(parseInt(getOption(args.positional, "--length")));
            const std::vector<std::uint8_t> data = ddr.read(offset, length);
            const std::string out_path = getOption(args.positional, "--out");
            if (!out_path.empty()) {
                writeBinaryFile(out_path, data);
                std::cout << "Read 0x" << std::hex << data.size() << " bytes from 0x" << offset << " -> " << out_path
                          << std::dec << '\n';
            } else {
                std::cout << formatHexDump(data, offset);
            }
        } else if (args.command == "write") {
            const std::uint64_t offset = parseInt(getOption(args.positional, "--offset"));
            const std::string hex = getOption(args.positional, "--hex");
            const std::string file = getOption(args.positional, "--file");
            if (hex.empty() == file.empty()) {
                throw XdmaDdr3Error("write requires exactly one of --hex or --file");
            }
            const std::vector<std::uint8_t> payload = hex.empty() ? readBinaryFile(file) : parseHexBytes(hex);
            const std::size_t count = ddr.write(offset, payload);
            std::cout << "Wrote 0x" << std::hex << count << " bytes to 0x" << offset << std::dec << '\n';
        } else if (args.command == "fill") {
            const std::uint64_t offset = parseInt(getOption(args.positional, "--offset"));
            const std::size_t length = static_cast<std::size_t>(parseInt(getOption(args.positional, "--length")));
            const std::string pattern_text = getOption(args.positional, "--pattern");
            const std::vector<std::uint8_t> pattern =
                pattern_text.empty() ? parseHexBytes("0x00000000") : parseHexBytes(pattern_text);
            const std::size_t count = ddr.fill(offset, length, pattern);
            std::cout << "Filled 0x" << std::hex << count << " bytes at 0x" << offset << std::dec << '\n';
        } else if (args.command == "verify") {
            const std::uint64_t offset = parseInt(getOption(args.positional, "--offset"));
            const std::string hex = getOption(args.positional, "--hex");
            const std::string file = getOption(args.positional, "--file");
            if (hex.empty() == file.empty()) {
                throw XdmaDdr3Error("verify requires exactly one of --hex or --file");
            }
            const std::vector<std::uint8_t> expected = hex.empty() ? readBinaryFile(file) : parseHexBytes(hex);
            const XdmaDdr3::VerifyResult result = ddr.verify(offset, expected);
            if (result.ok) {
                std::cout << "Verify PASS at 0x" << std::hex << offset << ", length 0x" << expected.size() << std::dec
                          << '\n';
            } else {
                std::cout << "Verify FAIL at 0x" << std::hex << (offset + result.mismatch_offset) << " (+0x"
                          << result.mismatch_offset << "), expected 0x" << std::setw(2) << std::setfill('0')
                          << static_cast<int>(result.expected_value) << std::dec << '\n';
                return 1;
            }
        } else if (args.command == "test") {
            runSelfTest(ddr, 0x0, 64 * 1024);
            runSelfTest(ddr, 0x100000, 64 * 1024);
            runSelfTest(ddr, 0x0, 64ULL * 1024 * 1024);
        } else if (args.command == "bench") {
            const std::string offset_text = getOption(args.positional, "--offset");
            const std::string size_text = getOption(args.positional, "--size");
            const std::string iterations_text = getOption(args.positional, "--iterations");
            const std::uint64_t offset = offset_text.empty() ? 0 : parseInt(offset_text);
            const std::size_t size = size_text.empty() ? (4U * 1024U * 1024U) : static_cast<std::size_t>(parseInt(size_text));
            const int iterations = iterations_text.empty() ? 10 : static_cast<int>(parseInt(iterations_text));
            runBandwidthTest(ddr, offset, size, iterations);
        } else {
            printUsage(argv[0]);
            throw XdmaDdr3Error("Unknown command: " + args.command);
        }
    } catch (const XdmaDdr3Error& exc) {
        std::cerr << "ERROR: " << exc.what() << '\n';
        return 1;
    }

    return 0;
}
