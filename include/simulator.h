#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "led_renderer.h"
#include "arduino_compat.h"
#include <memory>
#include <thread>
#include <atomic>

class WLEDSimulator {
public:
    WLEDSimulator(int numLeds = 100);
    ~WLEDSimulator();
    
    // Initialize the simulator
    bool init();
    
    // Start the simulator (main loop)
    void start();
    
    // Stop the simulator
    void stop();
    
    // Get the LED renderer
    LEDRenderer* getRenderer() { return renderer.get(); }
    
    // Network interface ports
    static constexpr int HTTP_PORT = 80;
    static constexpr int WEBSOCKET_PORT = 80;
    static constexpr int UDP_SYNC_PORT = 21324;
    static constexpr int ARTNET_PORT = 6454;
    static constexpr int SACN_PORT = 5568;
    
private:
    void simulatorLoop();
    void startHTTPServer();
    void startWebSocketServer();
    void startUDPSyncServer();
    void startArtNetServer();
    void startSACNServer();
    
    std::unique_ptr<LEDRenderer> renderer;
    std::atomic<bool> running;
    std::thread mainThread;
    int numLeds;
};

#endif // SIMULATOR_H
