#!/bin/bash
# Symbian Revival OS - Environment Setup Script
# Sets up the development environment for building SROS

set -e

echo "=========================================="
echo "Symbian Revival OS - Environment Setup"
echo "=========================================="
echo ""

# Detect OS
OS="$(uname -s)"
case "${OS}" in
    Linux*)     PLATFORM=Linux;;
    Darwin*)    PLATFORM=Mac;;
    CYGWIN*)    PLATFORM=Cygwin;;
    MINGW*)     PLATFORM=MinGw;;
    *)          PLATFORM="UNKNOWN:${OS}"
esac

echo "Detected platform: ${PLATFORM}"
echo ""

# Check prerequisites
echo "Checking prerequisites..."

command_exists() {
    command -v "$1" >/dev/null 2>&1
}

# Check for essential tools
MISSING_TOOLS=()

if ! command_exists cmake; then
    MISSING_TOOLS+=("cmake")
fi

if ! command_exists ninja; then
    MISSING_TOOLS+=("ninja-build")
fi

if ! command_exists gcc; then
    MISSING_TOOLS+=("gcc")
fi

if ! command_exists g++; then
    MISSING_TOOLS+=("g++")
fi

if ! command_exists python3; then
    MISSING_TOOLS+=("python3")
fi

if ! command_exists git; then
    MISSING_TOOLS+=("git")
fi

# Report missing tools
if [ ${#MISSING_TOOLS[@]} -gt 0 ]; then
    echo "ERROR: Missing required tools:"
    for tool in "${MISSING_TOOLS[@]}"; do
        echo "  - ${tool}"
    done
    echo ""
    echo "Please install missing tools:"
    if [ "$PLATFORM" = "Linux" ]; then
        echo "  sudo apt-get install -y build-essential cmake ninja-build gcc g++ python3 git"
    elif [ "$PLATFORM" = "Mac" ]; then
        echo "  brew install cmake ninja gcc g++ python3"
    fi
    exit 1
fi

echo "✓ All prerequisites found"
echo ""

# Check for Symbian source code
echo "Checking for Symbian OS source code..."
SYMBIAN_ROOT="./Symbian-OS/symbian-os"

if [ ! -d "${SYMBIAN_ROOT}/kernel" ]; then
    echo "WARNING: Symbian kernel source not found at ${SYMBIAN_ROOT}/kernel"
    echo ""
    echo "The Symbian OS source code is required to build SROS."
    echo "Please follow the instructions in SROS-Implemenation.md to download the source code."
    echo ""
    echo "Quick start:"
    echo "  cd Symbian-OS/symbian-os"
    echo "  git clone --depth=1 https://github.com/SymbianSource/oss.FCL.sf.os.kernelhwsrv.git kernel"
    echo "  git clone --depth=1 https://github.com/SymbianSource/oss.FCL.sf.os.graphics.git graphics"
    echo "  git clone --depth=1 https://github.com/SymbianSource/oss.FCL.sf.os.devicesrv.git devicesrv"
    echo ""
else
    echo "✓ Symbian kernel source found"
fi

echo ""
echo "=========================================="
echo "Setup Complete!"
echo "=========================================="
echo ""
echo "Next steps:"
echo "  1. Download Symbian OS source code (if not already done)"
echo "  2. mkdir build && cd build"
echo "  3. cmake -G Ninja -DCMAKE_BUILD_TYPE=Release .."
echo "  4. ninja"
echo ""
