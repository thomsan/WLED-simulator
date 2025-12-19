#ifndef LED_RENDERER_H
#define LED_RENDERER_H

#include <cstdint>
#include <vector>
#include <mutex>
#include <string>

// Structure to represent an RGB/RGBW LED
struct LED {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t w; // White channel (for RGBW LEDs)
    
    LED() : r(0), g(0), b(0), w(0) {}
    LED(uint8_t red, uint8_t green, uint8_t blue, uint8_t white = 0) 
        : r(red), g(green), b(blue), w(white) {}
};

class LEDRenderer {
public:
    LEDRenderer(int numLeds);
    ~LEDRenderer();
    
    // Set LED color
    void setPixel(int index, uint8_t r, uint8_t g, uint8_t b, uint8_t w = 0);
    void setPixel(int index, const LED& led);
    
    // Get LED color
    LED getPixel(int index) const;
    
    // Show/update LEDs (trigger display update)
    void show();
    
    // Clear all LEDs
    void clear();
    
    // Get number of LEDs
    int getNumLeds() const { return numLeds; }
    
    // Get LED data for rendering
    const std::vector<LED>& getLEDs() const { return leds; }
    
    // Render to console (simple ASCII visualization)
    void renderToConsole();
    
    // Render to HTTP server (simple HTML page)
    std::string renderToHTML();
    
private:
    int numLeds;
    std::vector<LED> leds;
    mutable std::mutex ledMutex;
};

#endif // LED_RENDERER_H
