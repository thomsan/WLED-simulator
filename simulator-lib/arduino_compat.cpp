#include "arduino_compat.h"
#include <cstdio>
#include <cstdarg>
#include <unistd.h>

static auto start_time = std::chrono::steady_clock::now();

unsigned long millis() {
    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time);
    return duration.count();
}

unsigned long micros() {
    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now - start_time);
    return duration.count();
}

void delay(unsigned long ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void delayMicroseconds(unsigned long us) {
    std::this_thread::sleep_for(std::chrono::microseconds(us));
}

void pinMode(uint8_t pin, uint8_t mode) {
    // Stub - no actual GPIO in simulator
}

void digitalWrite(uint8_t pin, uint8_t val) {
    // Stub - no actual GPIO in simulator
}

int digitalRead(uint8_t pin) {
    // Stub - no actual GPIO in simulator
    return LOW;
}

void SerialClass::begin(unsigned long baud) {
    // Stub - already using stdout
}

void SerialClass::println(const char* str) {
    printf("%s\n", str);
}

void SerialClass::print(const char* str) {
    printf("%s", str);
}

void SerialClass::printf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

SerialClass Serial;

void EEPROMClass::begin(size_t size) {
    // Stub - could implement file-based persistence
}

uint8_t EEPROMClass::read(int idx) {
    return 0;
}

void EEPROMClass::write(int idx, uint8_t val) {
    // Stub
}

void EEPROMClass::commit() {
    // Stub
}

EEPROMClass EEPROM;
