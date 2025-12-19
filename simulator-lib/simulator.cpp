#include "simulator.h"
#include <cstdio>
#include <cmath>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

WLEDSimulator::WLEDSimulator(int numLeds) 
    : numLeds(numLeds), running(false) {
    renderer = std::make_unique<LEDRenderer>(numLeds);
}

WLEDSimulator::~WLEDSimulator() {
    stop();
}

bool WLEDSimulator::init() {
    printf("Initializing WLED Simulator with %d LEDs...\n", numLeds);
    
    // Initialize network interfaces
    printf("Network interfaces will be available on:\n");
    printf("  HTTP/WebSocket: port %d\n", HTTP_PORT);
    printf("  UDP Sync: port %d\n", UDP_SYNC_PORT);
    printf("  Art-Net: port %d\n", ARTNET_PORT);
    printf("  sACN (E1.31): port %d\n", SACN_PORT);
    
    return true;
}

void WLEDSimulator::start() {
    if (running) {
        printf("Simulator is already running\n");
        return;
    }
    
    running = true;
    mainThread = std::thread(&WLEDSimulator::simulatorLoop, this);
    
    // Start network servers
    startHTTPServer();
    startUDPSyncServer();
    startArtNetServer();
    startSACNServer();
}

void WLEDSimulator::stop() {
    if (!running) {
        return;
    }
    
    running = false;
    if (mainThread.joinable()) {
        mainThread.join();
    }
}

void WLEDSimulator::simulatorLoop() {
    printf("Starting simulator main loop...\n");
    
    const double TWO_PI = 6.283185307179586;
    int frame = 0;
    while (running) {
        // Simple rainbow animation for demonstration
        // In a real implementation, this would call WLED's effect engine
        for (int i = 0; i < numLeds; i++) {
            double hue = (double)(i + frame) / numLeds;
            double r = std::sin(hue * TWO_PI) * 127.0 + 128.0;
            double g = std::sin((hue + 0.33) * TWO_PI) * 127.0 + 128.0;
            double b = std::sin((hue + 0.66) * TWO_PI) * 127.0 + 128.0;
            
            renderer->setPixel(i, (uint8_t)r, (uint8_t)g, (uint8_t)b);
        }
        
        renderer->show();
        
        // Render to console every 30 frames
        if (frame % 30 == 0) {
            renderer->renderToConsole();
        }
        
        frame++;
        delay(50); // ~20 FPS
    }
}

void WLEDSimulator::startHTTPServer() {
    // Placeholder for HTTP server
    // In a real implementation, this would start a lightweight HTTP server
    // to serve the WLED web interface and handle API requests
    printf("HTTP server placeholder started on port %d\n", HTTP_PORT);
}

void WLEDSimulator::startWebSocketServer() {
    // Placeholder for WebSocket server
    // Would handle real-time LED updates
    printf("WebSocket server placeholder started\n");
}

void WLEDSimulator::startUDPSyncServer() {
    // Placeholder for UDP sync server
    // Would handle WLED sync protocol for multi-device synchronization
    printf("UDP Sync server placeholder started on port %d\n", UDP_SYNC_PORT);
}

void WLEDSimulator::startArtNetServer() {
    // Placeholder for Art-Net server
    // Would handle Art-Net DMX protocol
    printf("Art-Net server placeholder started on port %d\n", ARTNET_PORT);
}

void WLEDSimulator::startSACNServer() {
    // Placeholder for sACN (E1.31) server
    // Would handle streaming ACN protocol
    printf("sACN server placeholder started on port %d\n", SACN_PORT);
}
