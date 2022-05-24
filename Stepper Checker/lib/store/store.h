#pragma once
#include <Arduino.h>
class Store{
    public:
    enum RunningState_t{
            Idle=0,
            MovingR=1,
            MovingL=2,
        };
        
        struct MainParam_t{
            uint32_t speedPps;
            uint16_t rampUpMs;
            uint16_t rampDwMs;
            RunningState_t runState;
        };


    Store();
    void setCurrentRunState(RunningState_t state);
    void modifySpeed(int8_t deltaPps);
    void modifyRampUp(int8_t deltaMs);
    void modifyRampDown(int8_t deltaMs);
    void setEnable(bool isEnabled);

    MainParam_t getParamAll();

    void saveToEEPROM();
    void loadFromEEPROM();
    
    private:
          
};