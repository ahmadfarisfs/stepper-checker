#pragma once
#include <Arduino.h>
class Buzzer{
  public:
    Buzzer(uint8_t pin);
    void buzz(uint16_t duration);
    void loop();
    void setup();
    private:
    uint8_t m_pin;
    unsigned long m_buzzerEndTime;
};