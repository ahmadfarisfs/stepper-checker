#pragma once
#include <Arduino.h>

namespace Data{

        enum ScreenSelectedItem_e{
            Speed=0,
            RampUp=1,
            RampDown=2,
            MotorEnable =3
        };
        enum MotorDirection_e{
            Forward,
            Reverse
        };
      enum MotorState_e{
        Idle,
        RampingUp,
        ConstantSpeed,
        RampingDown
    };
     struct MotorMoveParam_e{
        uint16_t rampUpMs;
        uint16_t speedPps;
        uint16_t rampDownMs;
    };
        struct ScreenMainParam_t{
            MotorMoveParam_e moveParam;
            ScreenSelectedItem_e selectedItem;
            MotorDirection_e direction;
            MotorState_e state;
            uint16_t currentSpeed;
            bool isEnabled;
        };

        enum ScreenPage_e{
            SplashScreen,
            MainScreen,
            SavedScreen
        };
}