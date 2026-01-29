// Simple test program for hardware detection module
#include <iostream>
#include "../src/hw_detection/hw_probe.h"

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "SROS Hardware Detection Test" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;

    // Create hardware probe
    sros::hw_detection::HardwareProbe probe;

    // Probe CPU
    std::cout << "Detecting CPU..." << std::endl;
    auto cpu_info = probe.probeCpu();
    
    std::cout << "  Architecture: " << cpu_info.architecture << std::endl;
    std::cout << "  Vendor:       " << cpu_info.vendor << std::endl;
    std::cout << "  Model:        " << cpu_info.model << std::endl;
    std::cout << "  Cores:        " << cpu_info.cores << std::endl;
    std::cout << "  64-bit:       " << (cpu_info.supports_64bit ? "Yes" : "No") << std::endl;
    std::cout << std::endl;

    // Probe memory
    std::cout << "Detecting Memory..." << std::endl;
    auto mem_info = probe.probeMemory();
    
    std::cout << "  Total:        " << (mem_info.total_bytes / (1024 * 1024)) << " MB" << std::endl;
    std::cout << "  Type:         " << mem_info.type << std::endl;
    std::cout << std::endl;

    // Probe buses
    std::cout << "Detecting Buses..." << std::endl;
    auto buses = probe.probeBuses();
    
    if (buses.empty()) {
        std::cout << "  No buses detected (implementation pending)" << std::endl;
    } else {
        for (const auto& bus : buses) {
            std::cout << "  " << bus.type << " (Bus " << bus.bus_id << ")" << std::endl;
        }
    }
    std::cout << std::endl;

    std::cout << "========================================" << std::endl;
    std::cout << "Hardware Detection Complete!" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}
