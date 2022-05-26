#pragma once
#include <Arduino.h>
class Motor{
    public:
    enum MovementType_e{
        Forward,
        Reverse
    };
    enum MovementStatus_e{
        Idle,
        RampingUp,
        ConstantSpeed,
        RampingDown
    };
    Motor(uint8_t enPin, uint8_t stepPin, uint8_t dirPin);
    MovementStatus_e getStatus();
    void moveStart(MovementType_e type,unsigned long timestamp);
    void moveStop(unsigned long timestamp);
    void setArmed(bool state);
    void loop(unsigned long currentTs);
    void setup();
    void setMoveParam(uint16_t rampUpMs, uint16_t speedPps, uint16_t rampDownMs);
private:
    uint8_t m_EnPin,m_StepPin, m_dirPin;
    MovementStatus_e m_currentStatus;
    MovementType_e m_currentMovement;
    unsigned long m_startMoveTs,m_stopMoveTs;
    unsigned long m_endOfRampTs;
    unsigned long m_lastStepTsMicros;
    bool m_enabled;
    uint16_t m_rampUpMs,  m_speedPps,  m_rampDownMs;
    uint16_t m_currentPps,m_startPps;//stop Pps always 0
    uint16_t m_stepInterValMicros;
    float m_accelPpsPerMs,m_deccelPpsPerMs;
};