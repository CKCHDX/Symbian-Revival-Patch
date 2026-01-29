# Getting Started with Symbian Revival OS

Welcome to SROS! This guide will help you set up your development environment and build the project.

## Overview

Symbian Revival OS (SROS) is a modern revival of Symbian OS with automatic hardware detection and support for multiple platforms (ARM, x86, x64).

## Quick Start (5 Minutes)

### 1. Prerequisites

First, ensure you have the required tools installed:

#### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install -y build-essential cmake ninja-build \
    gcc g++ python3 git
```

#### macOS
```bash
brew install cmake ninja gcc g++ python3
```

#### Windows
Use WSL2 with Ubuntu and follow the Ubuntu instructions.

### 2. Clone the Repository

```bash
git clone https://github.com/CKCHDX/Symbian-Revival-Patch.git
cd Symbian-Revival-Patch
```

### 3. Run Setup Script

```bash
./tools/setup.sh
```

This will:
- Check for required tools
- Verify your environment
- Tell you what's missing (if anything)

### 4. Build the Hardware Detection Module

```bash
mkdir build
cd build
cmake ..
make
```

This builds the hardware detection module without requiring Symbian source code.

**Output**: You'll get `lib/libhw_detection.a` - the hardware detection library.

## Next Steps

### Option A: Explore Without Symbian Source (Fastest)

You can work on the hardware detection layer and device profiles without the Symbian source:

1. **Add device profiles**: Create JSON files in `src/hw_detection/device_profiles/`
2. **Improve hardware detection**: Edit `src/hw_detection/hw_probe.cpp`
3. **Build and test**: `make` in the build directory

### Option B: Build Full OS (Requires Symbian Source)

To build a complete bootable OS, you need the Symbian OS source code:

1. **Download Symbian source** (~1.5 GB, 15-30 minutes):
   ```bash
   cd Symbian-OS/symbian-os
   
   # Essential repositories
   git clone --depth=1 https://github.com/SymbianSource/oss.FCL.sf.os.kernelhwsrv.git kernel
   git clone --depth=1 https://github.com/SymbianSource/oss.FCL.sf.os.graphics.git graphics
   git clone --depth=1 https://github.com/SymbianSource/oss.FCL.sf.os.devicesrv.git devicesrv
   
   cd ../..
   ```

2. **Rebuild** to include Symbian components:
   ```bash
   rm -rf build
   mkdir build
   cd build
   cmake ..
   make
   ```

## What You Can Do Now

### 1. Run the Setup Script
```bash
./tools/setup.sh
```
Checks your environment and guides you.

### 2. Build the Project
```bash
./tools/build.sh
```
Builds everything in one command.

### 3. Add a New Device Profile
Create a JSON file in `src/hw_detection/device_profiles/` for your device.
See existing examples: `generic_x86_64.json`, `generic_arm.json`.

### 4. Read the Documentation
- **[BUILD.md](docs/BUILD.md)** - Detailed build instructions
- **[CONTRIBUTING.md](CONTRIBUTING.md)** - How to contribute
- **[README.md](README.md)** - Project overview
- **[SROS-Implemenation.md](SROS-Implemenation.md)** - Implementation details

## Project Structure

```
Symbian-Revival-Patch/
├── CMakeLists.txt              # Build configuration
├── README.md                   # Project overview
├── CONTRIBUTING.md             # Contribution guidelines
├── LICENSE                     # License information
├── .gitignore                  # Git ignore rules
│
├── Symbian-OS/                 # Symbian OS components
│   ├── CMakeLists.txt         # Symbian build config
│   └── symbian-os/            # Cloned Symbian repositories
│       ├── kernel/            # (clone separately)
│       ├── graphics/          # (clone separately)
│       └── devicesrv/         # (clone separately)
│
├── src/                        # SROS source code
│   ├── hw_detection/          # Hardware detection engine
│   │   ├── hw_probe.cpp       # CPU/bus detection
│   │   ├── hw_probe.h         # Header file
│   │   └── device_profiles/   # JSON device configs
│   ├── hal/                   # Hardware abstraction layer
│   ├── drivers/               # Device drivers
│   ├── services/              # System services
│   └── frameworks/            # Application frameworks
│
├── docs/                       # Documentation
│   └── BUILD.md               # Build instructions
│
├── tools/                      # Build and utility scripts
│   ├── setup.sh               # Environment setup
│   └── build.sh               # Build script
│
├── tests/                      # Tests
│   ├── unit/
│   └── integration/
│
└── build/                      # Build artifacts (generated)
```

## Common Tasks

### Clean Build
```bash
rm -rf build
mkdir build
cd build
cmake ..
make
```

### Build for Different Architecture
```bash
./tools/build.sh Release arm-eabi
```

### Test Setup
```bash
./tools/setup.sh
```

## Troubleshooting

### "Command not found: cmake"
Install CMake: `sudo apt-get install cmake` (Ubuntu) or `brew install cmake` (macOS)

### "Symbian kernel not found"
You need to clone the Symbian source code. See "Option B" above.

### "Build failed"
1. Check prerequisites: `./tools/setup.sh`
2. Clean build: `rm -rf build`
3. Try again: `mkdir build && cd build && cmake .. && make`

### Still stuck?
Open an issue on GitHub: https://github.com/CKCHDX/Symbian-Revival-Patch/issues

## Learning Resources

- **[README.md](README.md)** - Full project vision
- **[SROS-Implemenation.md](SROS-Implemenation.md)** - Detailed implementation guide
- **[Symbian OS Architecture](https://github.com/SymbianSource)** - Original source code
- **[Contributing Guide](CONTRIBUTING.md)** - How to help

## What's Next?

After getting set up:

1. **Phase 1**: Build system is ready ✓
2. **Phase 2**: Hardware detection engine (current focus)
3. **Phase 3**: Touch and input support
4. **Phase 4**: Connectivity (WiFi, Bluetooth)
5. **Phase 5**: Multi-platform support
6. **Phase 6**: Integration and release

See [README.md](README.md) for the complete roadmap.

## Join the Community

- **GitHub Issues**: Report bugs, request features
- **GitHub Discussions**: Ask questions, share ideas
- **Pull Requests**: Contribute code

---

**Happy coding!** 🚀

Need help? Open an issue or check the documentation.
