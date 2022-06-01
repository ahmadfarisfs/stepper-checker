#pragma once
#include "manager.h"
class CallBinder{
    public:
    static void setManObj(StepperTesterManager *man);
    static void onStartLeft();
    static void onStartRight();
    static void onStopMotor();
    static void onPlusOne();
    static void onPlusTen();
    static void onMinusOne();
    static void onMinusTen();
    static void onEnter();
    static void onSave(); 
    static StepperTesterManager *m_man; 
};