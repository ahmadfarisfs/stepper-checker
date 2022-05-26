#include "motor.h"

Motor::Motor(uint8_t enPin, uint8_t stepPin, uint8_t dirPin)
{
    m_EnPin = enPin;
    m_StepPin = stepPin;
    m_dirPin = dirPin;
}

void Motor::moveStart(Motor::MovementType_e movType, unsigned long timestamp)
{
    // end of accel
    if (m_currentStatus == Idle ||
        (m_currentStatus == RampingDown && movType == m_currentMovement))
    {
        m_currentStatus = RampingUp;
        m_startMoveTs = timestamp;
        m_currentMovement = movType;
        m_startPps = m_currentPps;
    }
}

void Motor::moveStop(unsigned long timestamp)
{
    if (m_currentStatus != Idle)
    {
        m_stopMoveTs = timestamp;
        m_currentStatus = RampingDown;
        m_startPps = m_currentPps;
    }
}
void Motor::setArmed(bool state)
{
    m_enabled = state;
}
void Motor::setMoveParam(uint16_t rampUpMs, uint16_t speedPps, uint16_t rampDownMs)
{
    m_speedPps = speedPps;

    m_accelPpsPerMs = float(m_speedPps) / float(rampUpMs);
    m_deccelPpsPerMs = float(m_speedPps) / float(rampDownMs);
}
Motor::MovementStatus_e Motor::getStatus()
{
    return m_currentStatus;
}
void Motor::setup(){
    pinMode(m_EnPin, OUTPUT);
    pinMode(m_dirPin, OUTPUT);
    pinMode(m_StepPin, OUTPUT);
    digitalWrite(m_EnPin,LOW);
    digitalWrite(m_dirPin,LOW);
    digitalWrite(m_StepPin,LOW);
    m_currentStatus=Idle;
    
}
void Motor::loop(unsigned long currentMicros)
{

    if (m_currentStatus == RampingUp)
    {
        // calculate current speed
        m_currentPps = m_startPps + uint16_t(m_accelPpsPerMs * (currentMicros / 1000 - m_startMoveTs/1000));
        m_stepInterValMicros = (1000000.0 / m_currentPps);
    }
    else if (m_currentStatus == RampingDown)
    {
        int16_t currentPps = m_startPps - uint16_t(m_deccelPpsPerMs * (currentMicros / 1000 - m_stopMoveTs/1000));
        
        if (currentPps <0){
            m_currentPps = 0;
        }else{
            m_currentPps = uint16_t(currentPps);
        }

        m_stepInterValMicros = (1000000.0 / m_currentPps);
    }
    else
    {
        // do not change speed
    }

    if (m_currentPps >= m_speedPps && m_currentStatus == RampingUp)
    {
        m_currentStatus = ConstantSpeed;
    }

    if (m_currentPps == 0 && m_currentStatus == RampingDown)
    {
        m_currentStatus = Idle;
        m_currentPps = 0;
    }

    digitalWrite(m_EnPin, m_enabled);
    digitalWrite(m_dirPin, uint8_t(m_currentMovement));
    // if(m_currentType==Forward){
    // Serial.println(int16_t(m_currentPps));

    // }else{
    //         Serial.println(-(int16_t)m_currentPps);
    // }
    if (currentMicros > m_lastStepTsMicros + m_stepInterValMicros && m_currentStatus != Idle)
    {
        digitalWrite(m_StepPin, HIGH);
        delayMicroseconds(2); // minimum pulse width
        digitalWrite(m_StepPin, LOW);
        m_lastStepTsMicros = currentMicros;
    }
}