#include "blinky.h"

Blinky::Blinky(uint8_t pin){
m_pin = pin;
}

void Blinky::setup(){
    pinMode(m_pin,OUTPUT);
}

void Blinky::setDuration(uint16_t durationMs){
    m_dur = durationMs;
}

void Blinky::loop(){
    unsigned long currentMillis;
    if(currentMillis > m_lastChangeState + m_dur){
        digitalWrite(m_pin,!digitalRead(m_pin));
        m_lastChangeState = currentMillis;
    }
}
