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
    if (!m_stepper->isMotorRunning())
    {
        return Data::MotorState_e::Idle;
    }
    int32_t state = m_stepper->getCurrentAcceleration();

    if (state > 0)
    {
        return Data::MotorState_e::RampingUp;
    }
    else
    {
        return Data::MotorState_e::RampingDown;
    }

    return Data::MotorState_e::Idle;
};
Data::MotorDirection_e EnhancedMotor::getCurrentDir(){

};
uint16_t EnhancedMotor::getCurrentSpeedPps(){};
void EnhancedMotor::moveStart(Data::MotorDirection_e dir, unsigned long timestamp)
{
    m_stepper->setAcceleration(m_accel);
    if (dir == Data::MotorDirection_e::Forward)
    {

        m_stepper->runForward();
    }
    else
    {

        m_stepper->runBackward();
    }
};
void EnhancedMotor::moveStop(unsigned long timestamp)
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
};
bool EnhancedMotor::isArmed()
{
    return m_stepper->getEnablePinHighActive();
};
void EnhancedMotor::loop(unsigned long currentTs){};
void EnhancedMotor::setup()
{
    m_engine->init();
    m_stepper = m_engine->stepperConnectToPin(m_StepPin);
    if (m_stepper)
    {
        m_stepper->setDirectionPin(m_dirPin);
        m_stepper->setEnablePin(m_EnPin);
        m_stepper->setAutoEnable(false);
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