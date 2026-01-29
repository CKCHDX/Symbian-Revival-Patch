# SROS Source Code

This directory contains the implementation of Symbian Revival OS components.

## Directory Structure

### `/hal/` - Hardware Abstraction Layer
Platform-specific HAL implementations:
- `common/` - Shared HAL interfaces
- `arm_eabi/` - ARM-specific HAL
- `x86/` - x86-specific HAL
- `x64/` - x64-specific HAL

### `/drivers/` - Device Drivers
Device driver implementations:
- `touch/` - Touch controller drivers (Atmel, Synaptics, Cypress)
- `wifi/` - WiFi chipset drivers (Atheros, Broadcom, MediaTek)
- `bluetooth/` - Bluetooth drivers (4.0+)
- `storage/` - Storage drivers (eMMC, SD, NVMe)
- `display/` - Display drivers (LCD, OLED, eDP)

### `/hw_detection/` - Hardware Detection Engine
Automatic hardware detection and driver loading:
- `hw_probe.cpp/h` - CPU/bus detection
- `device_db_loader.cpp/h` - JSON profile loader
- `hal_selector.cpp/h` - HAL selection logic
- `driver_loader.cpp/h` - Dynamic driver loading
- `device_profiles/` - JSON device configurations

### `/services/` - Symbian Services
System services:
- `networking/` - Network stack
- `filesystem/` - File system
- `ipc/` - Inter-process communication
- `connectivity/` - Connectivity services

### `/frameworks/` - Application Frameworks
Application development frameworks:
- `qt/` - Qt/QML support
- `native/` - Native API
- `legacy_s60/` - S60 compatibility

## Building

Each component is built as part of the main CMake build system.
See the main `CMakeLists.txt` and `docs/BUILD.md` for details.

## Adding New Components

1. Create source files in the appropriate directory
2. Add to `CMakeLists.txt`
3. Document in component README
4. Add tests in `/tests/`

## Code Style

- Follow existing code style
- Use meaningful names
- Comment complex logic
- Keep functions focused

See `CONTRIBUTING.md` for detailed guidelines.
