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
    void moveStart(MovementType_e type);
    void moveStop();
    void setMoveParam(uint16_t rampUpMs, uint16_t speedPps, uint16_t rampDownMs);
};