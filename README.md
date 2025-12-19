# WLED Simulator

A virtual WLED renderer that integrates the [WLED](https://github.com/Aircoookie/WLED) repository as a submodule and provides a minimal UI to render virtual LEDs. The simulator runs as a Docker container with all necessary network interfaces exposed.

## Features

- **Virtual LED Strip**: Simulates up to 10,000 RGB/RGBW LEDs
- **Network Interfaces**: 
  - HTTP/WebSocket (Port 80)
  - UDP Sync (Port 21324)
  - Art-Net (Port 6454)
  - sACN/E1.31 (Port 5568)
- **WLED Integration**: Uses WLED codebase as a git submodule
- **Docker Support**: Easy deployment with Docker and docker-compose
- **Minimal UI**: Console and HTML-based LED visualization

## Quick Start

### Using Docker (Recommended)

1. Clone the repository with submodules:
```bash
git clone --recursive https://github.com/thomsan/WLED-simulator.git
cd WLED-simulator
```

2. Build and run with docker-compose:
```bash
docker-compose up --build
```

3. Access the simulator:
   - Console output will show the LED states
   - HTTP interface available at http://localhost:80

### Manual Build

#### Prerequisites
- CMake 3.16 or higher
- C++17 compatible compiler (GCC 7+, Clang 5+)
- Git (for submodules)

#### Build Steps

1. Clone with submodules:
```bash
git clone --recursive https://github.com/thomsan/WLED-simulator.git
cd WLED-simulator
```

2. Build:
```bash
mkdir build
cd build
cmake ..
make -j$(nproc)
```

3. Run:
```bash
./wled-simulator [num_leds]
```

Default is 100 LEDs. You can specify any number up to 10,000.

## Network Interfaces

The simulator exposes the following network interfaces for controlling the virtual LEDs:

| Interface | Port | Protocol | Description |
|-----------|------|----------|-------------|
| HTTP/WebSocket | 80 | TCP | Web interface and real-time control |
| UDP Sync | 21324 | UDP | WLED sync protocol for multi-device sync |
| Art-Net | 6454 | UDP | Art-Net DMX protocol |
| sACN (E1.31) | 5568 | UDP | Streaming ACN protocol |

## Configuration

### Number of LEDs

Specify the number of virtual LEDs when running:

```bash
# Docker
docker run -p 80:80 -p 21324:21324/udp -p 6454:6454/udp -p 5568:5568/udp wled-simulator 200

# Manual build
./wled-simulator 200
```

### Environment Variables (Docker)

Edit `docker-compose.yml` to configure:

```yaml
environment:
  - NUM_LEDS=200  # Number of virtual LEDs
```

## Project Structure

```
WLED-simulator/
├── WLED/                  # WLED submodule
├── src/                   # Main application source
│   └── main.cpp
├── include/               # Public headers
│   ├── arduino_compat.h
│   ├── led_renderer.h
│   └── simulator.h
├── simulator-lib/         # Simulator implementation
│   ├── arduino_compat.cpp
│   ├── led_renderer.cpp
│   └── simulator.cpp
├── CMakeLists.txt         # Build configuration
├── Dockerfile             # Docker image definition
├── docker-compose.yml     # Docker compose configuration
└── README.md
```

## Development

### Adding WLED Effects

The simulator is designed to integrate with WLED's effect engine. To add or modify effects:

1. Modify the effect code in the `WLED/wled00/` directory
2. Rebuild the simulator
3. Effects will be automatically available

### Extending Network Protocols

Network protocol handlers are in `simulator-lib/simulator.cpp`. To add support:

1. Implement the protocol handler function
2. Start the server in the `start()` method
3. Handle incoming messages and update the LED renderer

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

WLED is licensed under the MIT License - see [WLED License](https://github.com/Aircoookie/WLED/blob/main/LICENSE) for details.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## Acknowledgments

- [WLED Project](https://github.com/Aircoookie/WLED) - The amazing LED control software this simulator is based on
- Christian Schwinne (Aircoookie) - Creator of WLED
