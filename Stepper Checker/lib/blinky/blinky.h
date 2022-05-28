#pragma once
#include <Arduino.h>
class Blinky{
    public:
    Blinky(uint8_t pin);
    void setup();
    void setDuration(uint16_t durationMs);
    void loop();
    private:
    uint8_t m_pin;
    uint16_t m_dur;
    unsigned long m_lastChangeState;
};