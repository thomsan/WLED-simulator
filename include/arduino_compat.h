#ifndef ARDUINO_COMPAT_H
#define ARDUINO_COMPAT_H

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <thread>

// Arduino basic types
typedef std::string String;
typedef bool boolean;
typedef uint8_t byte;

// Arduino constants
#define HIGH 1
#define LOW 0
#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 2

// LED Strip Types (from WLED)
#define TYPE_WS2812_RGB 22
#define TYPE_SK6812_RGBW 30
#define TYPE_WS2811_400KHZ 40

// Arduino timing functions
unsigned long millis();
unsigned long micros();
void delay(unsigned long ms);
void delayMicroseconds(unsigned long us);

// Arduino digital I/O (stubs for simulator)
void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t val);
int digitalRead(uint8_t pin);

// Arduino serial (stub for simulator)
class SerialClass {
public:
    void begin(unsigned long baud);
    void println(const char* str);
    void print(const char* str);
    void printf(const char* fmt, ...);
};

extern SerialClass Serial;

// Math functions (use inline functions to avoid macro conflicts)
inline int absInt(int x) { return x > 0 ? x : -x; }
inline int constrainInt(int amt, int low, int high) { return amt < low ? low : (amt > high ? high : amt); }
inline int mapInt(int x, int in_min, int in_max, int out_min, int out_max) { 
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min; 
}
inline int minInt(int a, int b) { return a < b ? a : b; }
inline int maxInt(int a, int b) { return a > b ? a : b; }

// PROGMEM and FLASH storage macros (no-op on Linux)
#define PROGMEM
#define IRAM_ATTR
#define ICACHE_RAM_ATTR
#define pgm_read_byte(addr) (*(const uint8_t *)(addr))
#define pgm_read_word(addr) (*(const uint16_t *)(addr))
#define pgm_read_dword(addr) (*(const uint32_t *)(addr))
#define pgm_read_ptr(addr) (*(void * const *)(addr))
#define strlen_P strlen
#define strcpy_P strcpy
#define strcmp_P strcmp
#define strncmp_P strncmp

// WiFi and Network stubs
class IPAddress {
public:
    IPAddress() : addr{0, 0, 0, 0} {}
    IPAddress(uint8_t a, uint8_t b, uint8_t c, uint8_t d) : addr{a, b, c, d} {}
    uint8_t addr[4];
    operator bool() const { return addr[0] != 0 || addr[1] != 0 || addr[2] != 0 || addr[3] != 0; }
};

// EEPROM stub
class EEPROMClass {
public:
    void begin(size_t size);
    uint8_t read(int idx);
    void write(int idx, uint8_t val);
    void commit();
};

extern EEPROMClass EEPROM;

#endif // ARDUINO_COMPAT_H
