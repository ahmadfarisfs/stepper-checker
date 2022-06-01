#pragma once
#include <Arduino.h>

namespace Data
{

    enum ScreenSelectedItem_e
    {
        Speed = 0,
        RampUp = 1,
        RampDown = 2,
        MotorEnable = 3
    };
    enum MotorDirection_e
    {
        Forward = 0,
        Reverse = 1
    };
    enum MotorState_e
    {
        Idle,
        RampingUp,
        ConstantSpeed,
        RampingDown
    };
    struct MotorMoveParam_e
    {
        uint16_t rampUpMs;
        uint16_t speedPps;
        uint16_t rampDownMs;
    };
    struct ScreenMainParam_t
    {
        MotorMoveParam_e moveParam;
        ScreenSelectedItem_e selectedItem;
        MotorDirection_e direction;
        MotorState_e state;
        uint16_t currentSpeed;
        bool isEnabled;
    };

    enum ScreenPage_e
    {
        SplashScreen,
        MainScreen,
        SavedScreen,
        INITIAL
    };
  inline  bool operator!=(const ScreenMainParam_t &lhs, const ScreenMainParam_t &rhs)
    {
        if (lhs.currentSpeed != rhs.currentSpeed)
        {
            return true;
        }

        if (lhs.direction != rhs.direction)
        {
            return true;
        }
        if (lhs.isEnabled != rhs.isEnabled)
        {
            return true;
        }
        if (lhs.moveParam.rampDownMs != rhs.moveParam.rampDownMs)
        {
            return true;
        }
        if (lhs.moveParam.rampUpMs != rhs.moveParam.rampUpMs)
        {
            return true;
        }
        if (lhs.moveParam.speedPps != rhs.moveParam.speedPps)
        {
            return true;
        }

        if (lhs.selectedItem != rhs.selectedItem)
        {
            return true;
        }

        if (rhs.state != lhs.state)
        {
            return true;
        }

        return false;
    }
}