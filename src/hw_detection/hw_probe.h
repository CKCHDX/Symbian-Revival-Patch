// Hardware Detection Engine - Hardware Probe Module
// Detects CPU, memory, and hardware buses at boot time

#ifndef HW_PROBE_H
#define HW_PROBE_H

#include <cstdint>
#include <string>
#include <vector>

namespace sros {
namespace hw_detection {

/**
 * CPU Information structure
 */
struct CpuInfo {
    std::string architecture;  // "x86_64", "arm", "x86"
    std::string vendor;        // "Intel", "AMD", "ARM"
    std::string model;
    uint32_t cores;
    uint64_t frequency_mhz;
    bool supports_64bit;
};

/**
 * Memory Information structure
 */
struct MemoryInfo {
    uint64_t total_bytes;
    std::string type;  // "DDR3", "DDR4", "LPDDR3", etc.
};

/**
 * Bus Information structure
 */
struct BusInfo {
    std::string type;  // "I2C", "SPI", "SDIO", "USB", "PCI"
    uint32_t bus_id;
    std::vector<std::string> devices;
};

/**
 * Hardware Probe class
 * Detects hardware at boot time
 */
class HardwareProbe {
public:
    HardwareProbe();
    ~HardwareProbe();

    /**
     * Probe CPU information
     * @return CPU information structure
     */
    CpuInfo probeCpu();

    /**
     * Probe memory information
     * @return Memory information structure
     */
    MemoryInfo probeMemory();

    /**
     * Probe available buses
     * @return Vector of detected buses
     */
    std::vector<BusInfo> probeBuses();

    /**
     * Detect devices on a specific bus
     * @param bus_type Bus type (I2C, SPI, etc.)
     * @param bus_id Bus ID
     * @return Vector of device addresses/IDs
     */
    std::vector<std::string> detectBusDevices(const std::string& bus_type, uint32_t bus_id);

private:
    CpuInfo probeCpuX86_64();
    CpuInfo probeCpuArm();
    CpuInfo probeCpuX86();

    MemoryInfo probeMemoryLinux();
    
    std::vector<BusInfo> probeBusesLinux();
    std::vector<BusInfo> probeBusesArm();
};

} // namespace hw_detection
} // namespace sros

#endif // HW_PROBE_H
