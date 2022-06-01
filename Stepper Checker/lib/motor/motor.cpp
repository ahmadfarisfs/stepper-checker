#include "motor.h"

PrimitiveMotor::PrimitiveMotor(uint8_t enPin, uint8_t stepPin, uint8_t dirPin)
{
    m_EnPin = enPin;
    m_StepPin = stepPin;
    m_dirPin = dirPin;
}

uint16_t PrimitiveMotor::getCurrentSpeedPps()
{
    return m_currentPps;
};
Data::MotorDirection_e PrimitiveMotor::getCurrentDir()
{
    return m_currentDirection;
};
Data::MotorMoveParam_e PrimitiveMotor::getMoveParam()
{
    return m_moveParam;
}
void PrimitiveMotor::moveStart(Data::MotorDirection_e direction)
{
    unsigned long timestamp = millis();
    // end of accel
    if (m_currentState == Data::MotorState_e::Idle ||
        (m_currentState == Data::MotorState_e::RampingDown && direction == m_currentDirection))
    {
        m_currentState = Data::MotorState_e::RampingUp;
        m_startMoveTs = timestamp;
        m_currentDirection = direction;
        m_startPps = m_currentPps;
    }
}

void PrimitiveMotor::moveStop()
{
    unsigned long timestamp = millis();
    if (m_currentState != Data::MotorState_e::Idle)
    {
        m_stopMoveTs = timestamp;
        m_currentState = Data::MotorState_e::RampingDown;
        m_startPps = m_currentPps;
    }
}
bool PrimitiveMotor::isArmed()
{
    return m_enabled;
}
void PrimitiveMotor::setArmed(bool state)
{
    m_enabled = state;
}

// Data::MotorMoveParam_e Motor::getMoveParam(){
//     return m_moveParam;
// }

void PrimitiveMotor::setMoveParam(Data::MotorMoveParam_e param)
{
    m_moveParam = param;
    m_accelPpsPerMs = float(m_moveParam.speedPps) / float(m_moveParam.rampUpMs);
    m_deccelPpsPerMs = float(m_moveParam.speedPps) / float(m_moveParam.rampDownMs);
}
Data::MotorState_e PrimitiveMotor::getState()
{
    return m_currentState;
}
void PrimitiveMotor::setup()
{
    pinMode(m_EnPin, OUTPUT);
    pinMode(m_dirPin, OUTPUT);
    pinMode(m_StepPin, OUTPUT);
    digitalWrite(m_EnPin, LOW);
    digitalWrite(m_dirPin, LOW);
    digitalWrite(m_StepPin, LOW);
    m_currentState = Data::MotorState_e::Idle;
    setArmed(true);
}
void PrimitiveMotor::loop()
{
    unsigned long currentMicros = micros();
    if (m_currentState == Data::MotorState_e::RampingUp)
    {
        // calculate current speed
        m_currentPps = m_startPps + uint16_t(m_accelPpsPerMs * (currentMicros / 1000 - m_startMoveTs / 1000));
        m_stepInterValMicros = (1000000.0 / m_currentPps);
    }
    else if (m_currentState == Data::MotorState_e::RampingDown)
    {
        int16_t currentPps = m_startPps - uint16_t(m_deccelPpsPerMs * (currentMicros / 1000 - m_stopMoveTs / 1000));

        if (currentPps < 0)
        {
            m_currentPps = 0;
        }
        else
        {
            m_currentPps = uint16_t(currentPps);
        }

        m_stepInterValMicros = (1000000.0 / m_currentPps);
    }
    else
    {
        // do not change speed
    }

    if (m_currentPps >= m_moveParam.speedPps && m_currentState == Data::MotorState_e::RampingUp)
    {
        m_currentState = Data::MotorState_e::ConstantSpeed;
    }

    if (m_currentPps == 0 && m_currentState == Data::MotorState_e::RampingDown)
    {
        m_currentState = Data::MotorState_e::Idle;
        m_currentPps = 0;
    }

    digitalWrite(m_EnPin, m_enabled);
    digitalWrite(m_dirPin, uint8_t(m_currentDirection));
    if (m_currentDirection == Data::MotorDirection_e::Forward)
    {
        Serial.println(int16_t(m_currentPps));
    }
    else
    {
        Serial.println(-(int16_t)m_currentPps);
    }
    if (currentMicros > m_lastStepTsMicros + m_stepInterValMicros && m_currentState != Data::MotorState_e::Idle)
    {
        digitalWrite(m_StepPin, HIGH);
        delayMicroseconds(2); // minimum pulse width
        digitalWrite(m_StepPin, LOW);
        m_lastStepTsMicros = currentMicros;
    }
}