#include "led_renderer.h"
#include <cstdio>
#include <sstream>
#include <iomanip>

LEDRenderer::LEDRenderer(int numLeds) : numLeds(numLeds) {
    leds.resize(numLeds);
}

LEDRenderer::~LEDRenderer() {
}

void LEDRenderer::setPixel(int index, uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
    if (index >= 0 && index < numLeds) {
        std::lock_guard<std::mutex> lock(ledMutex);
        leds[index] = LED(r, g, b, w);
    }
}

void LEDRenderer::setPixel(int index, const LED& led) {
    if (index >= 0 && index < numLeds) {
        std::lock_guard<std::mutex> lock(ledMutex);
        leds[index] = led;
    }
}

LED LEDRenderer::getPixel(int index) const {
    if (index >= 0 && index < numLeds) {
        std::lock_guard<std::mutex> lock(ledMutex);
        return leds[index];
    }
    return LED();
}

void LEDRenderer::show() {
    // In a real implementation, this would update the display
    // For now, we just keep the LED state in memory
}

void LEDRenderer::clear() {
    std::lock_guard<std::mutex> lock(ledMutex);
    for (auto& led : leds) {
        led = LED();
    }
}

void LEDRenderer::renderToConsole() {
    std::lock_guard<std::mutex> lock(ledMutex);
    printf("\n=== LED Strip (%d LEDs) ===\n", numLeds);
    
    // Show first LEDs in a more detailed view
    const int MAX_CONSOLE_DISPLAY_LEDS = 20;
    int displayCount = numLeds < MAX_CONSOLE_DISPLAY_LEDS ? numLeds : MAX_CONSOLE_DISPLAY_LEDS;
    for (int i = 0; i < displayCount; i++) {
        const auto& led = leds[i];
        printf("LED %3d: R=%3d G=%3d B=%3d W=%3d ", i, led.r, led.g, led.b, led.w);
        
        // Simple ASCII color representation
        if (led.r > 128 || led.g > 128 || led.b > 128 || led.w > 128) {
            printf("█");
        } else if (led.r > 64 || led.g > 64 || led.b > 64 || led.w > 64) {
            printf("▓");
        } else if (led.r > 32 || led.g > 32 || led.b > 32 || led.w > 32) {
            printf("▒");
        } else if (led.r > 0 || led.g > 0 || led.b > 0 || led.w > 0) {
            printf("░");
        } else {
            printf("·");
        }
        printf("\n");
    }
    
    if (numLeds > displayCount) {
        printf("... and %d more LEDs\n", numLeds - displayCount);
    }
    printf("===========================\n");
}

std::string LEDRenderer::renderToHTML() {
    std::lock_guard<std::mutex> lock(ledMutex);
    std::stringstream html;
    
    html << "<!DOCTYPE html>\n";
    html << "<html>\n<head>\n";
    html << "<title>WLED Simulator</title>\n";
    html << "<meta http-equiv=\"refresh\" content=\"0.5\">\n";
    html << "<style>\n";
    html << "body { background: #000; color: #fff; font-family: monospace; padding: 20px; }\n";
    html << ".led-strip { display: flex; flex-wrap: wrap; gap: 5px; margin: 20px 0; }\n";
    html << ".led { width: 30px; height: 30px; border-radius: 50%; box-shadow: 0 0 10px rgba(255,255,255,0.3); }\n";
    html << "h1 { color: #0ff; }\n";
    html << "</style>\n";
    html << "</head>\n<body>\n";
    html << "<h1>WLED Simulator - " << numLeds << " LEDs</h1>\n";
    html << "<div class=\"led-strip\">\n";
    
    for (int i = 0; i < numLeds; i++) {
        const auto& led = leds[i];
        html << "<div class=\"led\" style=\"background: rgb(" 
             << (int)led.r << "," << (int)led.g << "," << (int)led.b << ");\"></div>\n";
    }
    
    html << "</div>\n";
    html << "<p>Auto-refresh enabled</p>\n";
    html << "</body>\n</html>\n";
    
    return html.str();
}
