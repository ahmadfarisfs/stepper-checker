#pragma once
#include <Arduino.h>
#include <data.h>
#include <imotor.h>

class PrimitiveMotor:public IMotor{
    public:
    PrimitiveMotor(uint8_t enPin, uint8_t stepPin, uint8_t dirPin);
    Data::MotorState_e getState();
    Data::MotorDirection_e getCurrentDir();
    uint16_t getCurrentSpeedPps();
    void moveStart(Data::MotorDirection_e dir);
    void moveStop();
    void setArmed(bool state);
    bool isArmed();
    void loop();
    void setup();
    void setMoveParam(Data::MotorMoveParam_e param);
    Data::MotorMoveParam_e getMoveParam();
private:
    uint8_t m_EnPin,m_StepPin, m_dirPin;
    Data::MotorMoveParam_e m_moveParam;
    Data::MotorState_e m_currentState;
    Data::MotorDirection_e m_currentDirection;
    unsigned long m_startMoveTs,m_stopMoveTs;
    unsigned long m_endOfRampTs;
    unsigned long m_lastStepTsMicros;
    bool m_enabled;
    uint16_t m_currentPps,m_startPps;//stop Pps always 0
    uint16_t m_stepInterValMicros;
    float m_accelPpsPerMs,m_deccelPpsPerMs;
};