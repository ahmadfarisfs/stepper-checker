#pragma once
#include "Arduino.h"

class Button
{
public:
    enum EventType_e
    {
        ButtonUp,
        ButtonDown,
        ButtonLongPress,
        ButtonLongPressInterval
    };
    Button(uint8_t pin, bool invert = false);
    void setup(uint16_t longPressMs, uint16_t longPressIntervalMs, uint16_t debounceTimeMs);
    void setCallback(EventType_e evt, void (*cb)(void));
    bool isPressed();
    void loop();

private:
    unsigned long m_lanonstdownTs, m_lastUpTs, m_lastChangeTs, m_debounceTimeMs;
    uint8_t m_pin;
    uint16_t m_lpTrigCount;
    bool m_lpTriggred;
    bool m_invert;
    bool m_lastIsPressed;
    uint16_t m_longPressMs, m_lpIntMs;
    void (*m_onDown)(void) ;
    void (*m_onUp)(void);
    void (*m_onLP)(void);
    void (*m_onLPInt)(void);
};