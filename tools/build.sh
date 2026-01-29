#!/bin/bash
# Symbian Revival OS - Build Script
# Builds the SROS kernel and components

set -e

echo "=========================================="
echo "Symbian Revival OS - Build Script"
echo "=========================================="
echo ""

# Configuration
BUILD_TYPE="${1:-Release}"
ARCH="${2:-x86_64}"
JOBS="${3:-$(nproc 2>/dev/null || echo 4)}"

echo "Build configuration:"
echo "  Build Type: ${BUILD_TYPE}"
echo "  Architecture: ${ARCH}"
echo "  Parallel Jobs: ${JOBS}"
echo ""

# Create build directory
BUILD_DIR="build/${ARCH}"
mkdir -p "${BUILD_DIR}"

echo "Configuring CMake..."
cd "${BUILD_DIR}"
cmake -G Ninja \
    -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" \
    -DPLATFORM="${ARCH}" \
    ../..

echo ""
echo "Building..."
ninja -j"${JOBS}"

echo ""
echo "=========================================="
echo "Build Complete!"
echo "=========================================="
echo ""
echo "Build artifacts located in: ${BUILD_DIR}"
echo ""
