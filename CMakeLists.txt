cmake_minimum_required(VERSION 3.16)
project(WLED-Simulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(Threads REQUIRED)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/simulator-lib
    ${CMAKE_SOURCE_DIR}/WLED/wled00
)

# Simulator library sources
set(SIMULATOR_SOURCES
    simulator-lib/simulator.cpp
    simulator-lib/led_renderer.cpp
    simulator-lib/arduino_compat.cpp
)

# Create simulator library
add_library(wled_simulator_lib ${SIMULATOR_SOURCES})
target_link_libraries(wled_simulator_lib Threads::Threads)

# Main executable
add_executable(wled-simulator src/main.cpp)
target_link_libraries(wled-simulator wled_simulator_lib Threads::Threads)

# Installation
install(TARGETS wled-simulator DESTINATION bin)
