#!/bin/bash
# Run script for WLED Simulator

# Default number of LEDs
NUM_LEDS=${1:-100}

echo "Starting WLED Simulator with $NUM_LEDS LEDs..."
echo ""

# Check if binary exists
if [ ! -f "build/wled-simulator" ]; then
    echo "Error: Simulator binary not found!"
    echo "Please run ./build.sh first to build the project."
    exit 1
fi

# Run the simulator
./build/wled-simulator $NUM_LEDS
