# Building Symbian Revival OS

This guide covers building SROS from source.

## Prerequisites

### Ubuntu/Debian
```bash
sudo apt-get install -y build-essential cmake ninja-build \
    gcc-arm-none-eabi gcc g++ binutils python3 git
```

### macOS
```bash
brew install cmake ninja gcc g++ python3
```

### Windows
Use WSL2 with Ubuntu and follow the Ubuntu instructions above.

## Quick Start

### 1. Clone the Repository
```bash
git clone https://github.com/CKCHDX/Symbian-Revival-Patch.git
cd Symbian-Revival-Patch
```

### 2. Run Setup Script
```bash
./tools/setup.sh
```

This will verify your environment and check for required tools.

### 3. Download Symbian OS Source Code

The Symbian OS source code is hosted on GitHub SymbianSource organization.
You need to clone the essential repositories:

```bash
cd Symbian-OS/symbian-os

# Essential repositories (~1.5 GB, 15-30 minutes)
git clone --depth=1 https://github.com/SymbianSource/oss.FCL.sf.os.kernelhwsrv.git kernel
git clone --depth=1 https://github.com/SymbianSource/oss.FCL.sf.os.graphics.git graphics
git clone --depth=1 https://github.com/SymbianSource/oss.FCL.sf.os.devicesrv.git devicesrv

cd ../..
```

### 4. Build
```bash
# Using the build script
./tools/build.sh Release x86_64

# Or manually
mkdir -p build/x86_64
cd build/x86_64
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DPLATFORM=x86_64 ../..
ninja -j$(nproc)
```

## Build Options

### Build Types
- `Release` - Optimized for performance (default)
- `Debug` - Includes debug symbols, no optimization
- `RelWithDebInfo` - Optimized with debug symbols

### Architectures
- `x86_64` - 64-bit x86 (default)
- `x86` - 32-bit x86
- `arm-eabi` - ARM EABI

### Examples

```bash
# Debug build for ARM
./tools/build.sh Debug arm-eabi

# Release build for x86
./tools/build.sh Release x86

# Default (Release x86_64)
./tools/build.sh
```

## Build Artifacts

After a successful build, artifacts will be located in:
```
build/<architecture>/artifacts/
├── kernel/       # Kernel binaries
├── drivers/      # Driver modules
└── system/       # System libraries
```

## Troubleshooting

### Missing Prerequisites
If you get errors about missing tools, run:
```bash
./tools/setup.sh
```
It will tell you which tools are missing and how to install them.

### Symbian Source Not Found
Make sure you've cloned the Symbian OS source code into `Symbian-OS/symbian-os/`.
See step 3 above or refer to `SROS-Implemenation.md` for complete instructions.

### Build Errors
1. Clean the build directory:
   ```bash
   rm -rf build/
   ```

2. Re-run setup:
   ```bash
   ./tools/setup.sh
   ```

3. Try building again:
   ```bash
   ./tools/build.sh
   ```

## Next Steps

After building:
1. Test on QEMU emulator (see `tools/emulator_runner.sh`)
2. Create device profiles (see `src/hw_detection/device_profiles/`)
3. Add device drivers (see `docs/DRIVER_DEVELOPMENT.md`)

## More Information

- [SROS Implementation Guide](../SROS-Implemenation.md)
- [Project README](../README.md)
- [Architecture Documentation](./ARCHITECTURE.md)
