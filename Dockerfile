FROM ubuntu:22.04

# Install build dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy project files
COPY . .

# Initialize submodules
RUN git submodule update --init --recursive || true

# Build the simulator
RUN mkdir -p build && \
    cd build && \
    cmake .. && \
    make -j$(nproc)

# Expose ports for network interfaces
EXPOSE 80       
EXPOSE 21324    
EXPOSE 6454     
EXPOSE 5568     

# Run the simulator
CMD ["./build/wled-simulator", "100"]
