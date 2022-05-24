#pragma once
#include "Arduino.h"
#include <nonstd.h>
class Button{
    public:
    enum EventType_e{
        ButtonUp,
        ButtonDown,
        ButtonLongPress,
        ButtonLongPressInterval
    };
    Button(uint8_t pin, bool invert = false);
    void setup(uint16_t longPressMs,uint16_t longPressIntervalMs,uint16_t debounceTimeMs);
    void setCallback(EventType_e evt, nonstd::function<void (void)> cb);
    bool isPressed();
    void loop();
    private:
    unsigned long m_lanonstdownTs,m_lastUpTs,m_lastChangeTs,m_debounceTimeMs;
    uint8_t m_pin;
    uint16_t m_lpTrigCount;
    bool m_lpTriggred;
    bool m_invert;
    bool m_lastIsPressed;
    uint16_t m_longPressMs,m_lpIntMs;
    nonstd::function<void (void)> m_onDown;
    nonstd::function<void (void)> m_onUp;
    nonstd::function<void (void)> m_onLP;
    nonstd::function<void (void)> m_onLPInt;
};