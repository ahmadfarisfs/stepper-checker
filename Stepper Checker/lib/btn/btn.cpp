#include <Arduino.h>
#include <btn.h>
// #include <ArduinoSTL.h>
// #include <nonstd.h>

Button::Button(uint8_t pin, bool invert)
{
    m_pin = pin;
    m_invert = invert;
    m_lastIsPressed = false;
}

void Button::setup(uint16_t longPressMs, uint16_t longPressIntervalMs, uint16_t debounceTimeMs)
{
    pinMode(m_pin, INPUT_PULLUP);
    m_lastIsPressed = isPressed();
    m_longPressMs = longPressMs;
    m_lpIntMs = longPressIntervalMs;
    m_debounceTimeMs = debounceTimeMs;
}

void Button::setCallback(EventType_e evt, void (*cb)(void))
{
    switch (evt)
    {
    case EventType_e::ButtonDown:
        m_onDown = cb;
        break;
    case EventType_e::ButtonUp:
        m_onUp = cb;
        break;
    case EventType_e::ButtonLongPress:
        m_onLP = cb;
        break;

    case EventType_e::ButtonLongPressInterval:
        m_onLPInt = cb;
        break;
    default:
        break;
    }
}

bool Button::isPressed()
{
    return m_invert ? !digitalRead(m_pin) : digitalRead(m_pin);
}

void Button::loop()
{
    bool currentIsPressed = isPressed();
    if (currentIsPressed != m_lastIsPressed)
    {
        // debounce
        if (millis() < m_lastChangeTs + m_debounceTimeMs)
        {
            return;
        }
        m_lastChangeTs = millis();
    }

    if (currentIsPressed && !m_lastIsPressed)
    {
        // down event
        m_lanonstdownTs = millis();
        if (m_onDown!=nullptr)
        {
            m_onDown();
        }
    }
    if (!currentIsPressed && m_lastIsPressed)
    {
        // up event
        m_lastUpTs = millis();
        m_lpTriggred = false;
        m_lpTrigCount = 0;
        if (m_onUp!=nullptr)
        {
            m_onUp();
        }
    }
    if (currentIsPressed && m_lastIsPressed)
    {
        // button currently pressed
        unsigned long currentMs = millis();

        // long press callback
        if (currentMs > m_lanonstdownTs + m_longPressMs && !m_lpTriggred)
        {
            m_lpTriggred = true;
            if (m_onLP!=nullptr)
            {
                m_onLP();
            }
        }

        // interval LP callback
        unsigned long durAfterLP = currentMs - (m_lanonstdownTs + m_longPressMs);
        if (m_lpTriggred && (uint16_t)(durAfterLP / m_lpIntMs) > m_lpTrigCount)
        {
            m_lpTrigCount++;
            if (m_onLPInt!=nullptr)
            {
                m_onLPInt();
            }
        }
    }

    m_lastIsPressed = currentIsPressed;
}