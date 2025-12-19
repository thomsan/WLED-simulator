#include "simulator.h"
#include <cstdio>
#include <cstdlib>
#include <csignal>
#include <memory>

static std::unique_ptr<WLEDSimulator> simulator;

void signalHandler(int signum) {
    printf("\nReceived signal %d, shutting down...\n", signum);
    if (simulator) {
        simulator->stop();
    }
    exit(signum);
}

int main(int argc, char* argv[]) {
    // Parse command line arguments
    int numLeds = 100; // Default number of LEDs
    
    if (argc > 1) {
        numLeds = atoi(argv[1]);
        if (numLeds <= 0 || numLeds > 10000) {
            fprintf(stderr, "Invalid number of LEDs. Using default (100)\n");
            numLeds = 100;
        }
    }
    
    printf("========================================\n");
    printf("       WLED Simulator v0.1.0\n");
    printf("========================================\n");
    printf("Virtual LED Strip: %d LEDs\n", numLeds);
    printf("========================================\n\n");
    
    // Set up signal handlers
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
    
    // Create and initialize simulator
    simulator = std::make_unique<WLEDSimulator>(numLeds);
    
    if (!simulator->init()) {
        fprintf(stderr, "Failed to initialize simulator\n");
        return 1;
    }
    
    // Start simulator
    printf("\nStarting simulator...\n");
    printf("Press Ctrl+C to stop\n\n");
    
    simulator->start();
    
    // Keep the main thread alive
    while (true) {
        delay(1000);
    }
    
    return 0;
}
