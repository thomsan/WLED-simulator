#!/bin/bash
# Build script for WLED Simulator

set -e

echo "========================================="
echo "  Building WLED Simulator"
echo "========================================="

# Create build directory if it doesn't exist
if [ ! -d "build" ]; then
    mkdir build
fi

cd build

# Run CMake
echo "Running CMake..."
cmake ..

# Build
echo "Building..."
make -j$(nproc)

echo ""
echo "========================================="
echo "  Build completed successfully!"
echo "========================================="
echo ""
echo "Run the simulator with:"
echo "  ./build/wled-simulator [num_leds]"
echo ""
