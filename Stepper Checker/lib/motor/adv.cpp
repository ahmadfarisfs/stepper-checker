#include "adv.h"
#include "FastAccelStepper.h"

EnhancedMotor::EnhancedMotor(uint8_t enPin, uint8_t stepPin, uint8_t dirPin,FastAccelStepperEngine *engine, FastAccelStepper *stepper)
{
    m_EnPin = enPin;
    m_StepPin = stepPin;
    m_dirPin = dirPin;
    m_engine = engine;
    m_stepper = stepper;
};
Data::MotorState_e EnhancedMotor::getState()
{
    if (!m_stepper->isRunning())
    {
        return Data::MotorState_e::Idle;
    }

    int32_t state = m_stepper->getCurrentAcceleration();

    if (state > 0)
    {
        return Data::MotorState_e::RampingUp;
    }
    else if (state <0)
    {
        return Data::MotorState_e::RampingDown;
    }else{
        return Data::MotorState_e::ConstantSpeed;
    }

};
Data::MotorDirection_e EnhancedMotor::getCurrentDir(){
    return m_currentDir;
};
uint16_t EnhancedMotor::getCurrentSpeedPps(){
    return uint16_t(abs(float(m_stepper->getCurrentSpeedInMilliHz())/1000.0));
};
void EnhancedMotor::moveStart(Data::MotorDirection_e dir)
{
    
    m_stepper->setAcceleration(m_accel);
    if (dir == Data::MotorDirection_e::Forward)
    {m_currentDir = Data::MotorDirection_e::Forward;
        m_stepper->runForward();
    }
    else
    {
        m_currentDir = Data::MotorDirection_e::Reverse;
        m_stepper->runBackward();
    }
};
void EnhancedMotor::moveStop()
{
    m_stepper->setAcceleration(m_deccel);
    m_stepper->stopMove();
};
void EnhancedMotor::setArmed(bool state)
{
    if (state)
    {
        m_stepper->enableOutputs();
    }
    else
    {
        m_stepper->disableOutputs();
    }
    m_isEnabled = state;
};
bool EnhancedMotor::isArmed()
{
    return m_isEnabled;
};
void EnhancedMotor::loop(){};
void EnhancedMotor::setup()
{
    m_engine->init();
    m_stepper = m_engine->stepperConnectToPin(m_StepPin);
    if (m_stepper)
    {
        m_stepper->setDirectionPin(m_dirPin);
        m_stepper->setEnablePin(m_EnPin);
        m_stepper->setAutoEnable(false);
        m_stepper->enableOutputs();
        m_isEnabled = true; // enable state must be shadowed
    }
};
void EnhancedMotor::setMoveParam(Data::MotorMoveParam_e param)
{m_speed = param.speedPps;
    m_accel = m_speed / (param.rampUpMs / 1000.0);
    m_deccel = m_speed / (param.rampDownMs / 1000.0);
    m_param = param;
    m_stepper->setSpeedInHz(m_speed);
};
Data::MotorMoveParam_e EnhancedMotor::getMoveParam(){
    return m_param;
};