#include "store.h"

   Store::Store(){};
    void Store::modifySpeed(int8_t deltaPps){};
    void Store::modifyRampUp(int8_t deltaMs){};
    void Store::modifyRampDown(int8_t deltaMs){};
    void Store::setEnable(bool isEnabled){};
        void Store::saveToEEPROM(){};
    void Store::loadFromEEPROM(){};

     void Store::setCurrentRunState(RunningState_t state){};
      Store::MainParam_t getParamAll(){};