#pragma once
#include <Arduino.h>

namespace Data{
            enum SelectedItem_t{
            Speed=0,
            RampUp=1,
            RampDown=2,
            MotorEnable =3
        };
            struct MainParam_t{
            uint16_t speedPps;
            uint16_t rampUpMs;
            uint16_t rampDwMs;
            SelectedItem_t selectedItem;
    bool isEnabled;
            uint8_t saveProgress;
        };

                enum Page_t{
            SplashScreen,
            MainScreen,
            SavedScreen
        };
}