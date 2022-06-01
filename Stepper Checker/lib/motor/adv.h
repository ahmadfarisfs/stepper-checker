#pragma once
#include "motor.h"
#include "FastAccelStepper.h"
class EnhancedMotor : public IMotor{
    public:
    EnhancedMotor::EnhancedMotor(uint8_t enPin, uint8_t stepPin, uint8_t dirPin,FastAccelStepperEngine *engine, FastAccelStepper *stepper);
    Data::MotorState_e getState();
    Data::MotorDirection_e getCurrentDir();
    uint16_t getCurrentSpeedPps();
    void moveStart(Data::MotorDirection_e dir,unsigned long timestamp);
    void moveStop(unsigned long timestamp);
    void setArmed(bool state);
    bool isArmed();
    void loop(unsigned long currentTs);
    void setup();
    void setMoveParam(Data::MotorMoveParam_e param);
    Data::MotorMoveParam_e getMoveParam();
    private:
    Data::MotorMoveParam_e m_param;
    uint32_t m_accel,m_deccel,m_speed;
    uint8_t m_EnPin,m_StepPin, m_dirPin;
    FastAccelStepperEngine *m_engine ;//= FastAccelStepperEngine();
    FastAccelStepper *m_stepper;// = NULL;
};