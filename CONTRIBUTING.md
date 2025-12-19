# Contributing to WLED Simulator

Thank you for your interest in contributing to the WLED Simulator project!

## Development Setup

### Prerequisites

- C++17 compatible compiler (GCC 7+ or Clang 5+)
- CMake 3.16 or higher
- Git (for submodules)
- Docker (optional, for containerized builds)

### Getting Started

1. Clone the repository with submodules:
```bash
git clone --recursive https://github.com/thomsan/WLED-simulator.git
cd WLED-simulator
```

2. Build the project:
```bash
./build.sh
```

3. Run the simulator:
```bash
./run.sh [num_leds]
```

## Project Structure

- `src/` - Main application entry point
- `include/` - Public header files
- `simulator-lib/` - Core simulator implementation
  - `arduino_compat.cpp` - Arduino compatibility layer
  - `led_renderer.cpp` - LED visualization engine
  - `simulator.cpp` - Main simulator logic
- `WLED/` - WLED git submodule (upstream project)
- `CMakeLists.txt` - Build configuration
- `Dockerfile` - Container image definition

## Development Guidelines

### Code Style

- Use C++17 features where appropriate
- Follow existing code formatting
- Keep functions focused and modular
- Add comments for complex logic

### Adding Features

When adding new features:

1. Start with a minimal implementation
2. Test locally before committing
3. Update documentation in README.md
4. Add comments explaining complex logic

### Network Protocol Implementation

To implement a network protocol (UDP Sync, Art-Net, sACN, etc.):

1. Add server initialization in `simulator.cpp`
2. Create a protocol handler function
3. Parse incoming messages
4. Update LED renderer with received data
5. Test with appropriate clients

### WLED Integration

The project uses WLED as a submodule. To integrate WLED effects:

1. Study WLED's FX engine in `WLED/wled00/FX.cpp`
2. Create wrapper functions in `simulator-lib/`
3. Map WLED's hardware abstraction to simulator
4. Test effects render correctly

## Testing

Before submitting changes:

1. Build and run the simulator
2. Verify LED visualization works
3. Test with different LED counts
4. Check for memory leaks (if adding new features)
5. Test Docker build if modifying build system

## Docker Development

Build and test with Docker:

```bash
docker build -t wled-simulator .
docker run --rm -p 80:80 -p 21324:21324/udp -p 6454:6454/udp -p 5568:5568/udp wled-simulator
```

## Submitting Changes

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request with:
   - Clear description of changes
   - Why the change is needed
   - How to test the changes

## Questions?

Open an issue on GitHub if you have questions or need help!
