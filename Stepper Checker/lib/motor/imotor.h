#pragma once
#include "data.h"
class IMotor{
    public:
   virtual Data::MotorState_e getState()=0;
   virtual Data::MotorDirection_e getCurrentDir()=0;
   virtual uint16_t getCurrentSpeedPps()=0;
   virtual void moveStart(Data::MotorDirection_e dir)=0;
   virtual void moveStop()=0;
   virtual void setArmed(bool state)=0;
   virtual bool isArmed()=0;
   virtual void loop()=0;
   virtual void setup()=0;
   virtual void setMoveParam(Data::MotorMoveParam_e param)=0;
   virtual Data::MotorMoveParam_e getMoveParam()=0;
};