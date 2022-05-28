#include "bzr.h"

Buzzer::Buzzer(uint8_t pin){
    m_pin=pin;
}

void Buzzer::setup(){
    pinMode(m_pin,OUTPUT);
}

void Buzzer::buzz(uint16_t duration){
    //Do not interrupt ongoing beep
    if (digitalRead(m_pin))
    {
        return;
    }
    digitalWrite(m_pin, HIGH);
    m_buzzerEndTime = millis() + duration;
}

void Buzzer::loop(){
    if (millis() > m_buzzerEndTime)
    {
        digitalWrite(m_pin, LOW);
    }
}