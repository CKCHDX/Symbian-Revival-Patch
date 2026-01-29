// Hardware Detection Engine - Hardware Probe Implementation
// Detects CPU, memory, and hardware buses at boot time

#include "hw_probe.h"
#include <fstream>
#include <sstream>
#include <cstring>

#ifdef __x86_64__
#include <cpuid.h>
#endif

namespace sros {
namespace hw_detection {

HardwareProbe::HardwareProbe() {
    // Constructor
}

HardwareProbe::~HardwareProbe() {
    // Destructor
}

CpuInfo HardwareProbe::probeCpu() {
#ifdef __x86_64__
    return probeCpuX86_64();
#elif defined(__arm__) || defined(__aarch64__)
    return probeCpuArm();
#elif defined(__i386__)
    return probeCpuX86();
#else
    CpuInfo info;
    info.architecture = "unknown";
    info.vendor = "unknown";
    info.model = "unknown";
    info.cores = 1;
    info.frequency_mhz = 0;
    info.supports_64bit = false;
    return info;
#endif
}

CpuInfo HardwareProbe::probeCpuX86_64() {
    CpuInfo info;
    info.architecture = "x86_64";
    info.supports_64bit = true;

#ifdef __x86_64__
    // Read CPU vendor string using CPUID
    unsigned int eax, ebx, ecx, edx;
    char vendor[13];
    
    if (__get_cpuid(0, &eax, &ebx, &ecx, &edx)) {
        memcpy(vendor, &ebx, 4);
        memcpy(vendor + 4, &edx, 4);
        memcpy(vendor + 8, &ecx, 4);
        vendor[12] = '\0';
        info.vendor = vendor;
    } else {
        info.vendor = "unknown";
    }

    // Read CPU model from /proc/cpuinfo
    std::ifstream cpuinfo("/proc/cpuinfo");
    if (cpuinfo.is_open()) {
        std::string line;
        while (std::getline(cpuinfo, line)) {
            if (line.find("model name") != std::string::npos) {
                size_t pos = line.find(":");
                if (pos != std::string::npos) {
                    info.model = line.substr(pos + 2);
                }
                break;
            }
        }
        cpuinfo.close();
    }

    // Count cores
    cpuinfo.open("/proc/cpuinfo");
    if (cpuinfo.is_open()) {
        std::string line;
        info.cores = 0;
        while (std::getline(cpuinfo, line)) {
            if (line.find("processor") != std::string::npos) {
                info.cores++;
            }
        }
        cpuinfo.close();
    }
#endif

    if (info.model.empty()) {
        info.model = "Generic x86_64";
    }
    if (info.cores == 0) {
        info.cores = 1;
    }

    return info;
}

CpuInfo HardwareProbe::probeCpuArm() {
    CpuInfo info;
    info.architecture = "arm";
    info.vendor = "ARM";
    info.supports_64bit = false;

#ifdef __aarch64__
    info.architecture = "arm64";
    info.supports_64bit = true;
#endif

    // Try to read from /proc/cpuinfo
    std::ifstream cpuinfo("/proc/cpuinfo");
    if (cpuinfo.is_open()) {
        std::string line;
        while (std::getline(cpuinfo, line)) {
            if (line.find("Hardware") != std::string::npos ||
                line.find("model name") != std::string::npos) {
                size_t pos = line.find(":");
                if (pos != std::string::npos) {
                    info.model = line.substr(pos + 2);
                }
            }
            if (line.find("processor") != std::string::npos) {
                info.cores++;
            }
        }
        cpuinfo.close();
    }

    if (info.model.empty()) {
        info.model = "Generic ARM";
    }
    if (info.cores == 0) {
        info.cores = 1;
    }

    return info;
}

CpuInfo HardwareProbe::probeCpuX86() {
    CpuInfo info;
    info.architecture = "x86";
    info.vendor = "unknown";
    info.model = "Generic x86";
    info.cores = 1;
    info.frequency_mhz = 0;
    info.supports_64bit = false;
    return info;
}

MemoryInfo HardwareProbe::probeMemory() {
    return probeMemoryLinux();
}

MemoryInfo HardwareProbe::probeMemoryLinux() {
    MemoryInfo info;
    info.total_bytes = 0;
    info.type = "unknown";

    // Read from /proc/meminfo
    std::ifstream meminfo("/proc/meminfo");
    if (meminfo.is_open()) {
        std::string line;
        while (std::getline(meminfo, line)) {
            if (line.find("MemTotal:") != std::string::npos) {
                std::istringstream iss(line);
                std::string label;
                uint64_t kb;
                iss >> label >> kb;
                info.total_bytes = kb * 1024;  // Convert to bytes
                break;
            }
        }
        meminfo.close();
    }

    // Default type (can be enhanced with DMI decoding)
    info.type = "DDR3/DDR4";

    return info;
}

std::vector<BusInfo> HardwareProbe::probeBuses() {
#if defined(__linux__)
    return probeBusesLinux();
#else
    return std::vector<BusInfo>();
#endif
}

std::vector<BusInfo> HardwareProbe::probeBusesLinux() {
    std::vector<BusInfo> buses;

    // TODO: Implement actual bus detection
    // This would scan /sys/bus/, /dev/, etc.
    
    // Placeholder: Add common buses
    BusInfo usb;
    usb.type = "USB";
    usb.bus_id = 0;
    buses.push_back(usb);

    BusInfo pci;
    pci.type = "PCI";
    pci.bus_id = 0;
    buses.push_back(pci);

    return buses;
}

std::vector<BusInfo> HardwareProbe::probeBusesArm() {
    std::vector<BusInfo> buses;

    // TODO: Implement ARM-specific bus detection
    // This would scan device tree, I2C, SPI, SDIO buses
    
    return buses;
}

std::vector<std::string> HardwareProbe::detectBusDevices(
    const std::string& bus_type, 
    uint32_t bus_id) {
    
    std::vector<std::string> devices;
    
    // TODO: Implement device detection per bus
    // This would enumerate devices on I2C, SPI, USB, etc.
    
    return devices;
}

} // namespace hw_detection
} // namespace sros
