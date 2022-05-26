#pragma once
#include <Arduino.h>
// #include <U8g2lib.h>
#include "btn.h"
#include "motor.h"
#include "data.h"
#include "lcd.h"

#define MAX_BUTTON_NUM 5
class StepperTesterManager{
        
    public:


        // enum EventType_e {
        //     OnMoveStartFwd,
        //     OnMoveStartRev,
        //     OnMoveStop,
        // };
        // enum RunningState_t{
        //     Idle=0,
        //     MovingR=1,
        //     MovingL=2,
        // };

        StepperTesterManager( Button *up, Button*down,  Button*plus,  Button*minus, Button*enter,Motor * motor, LCD *lcd);
        void setup();
        // void onEvent();        
        // void enableRender();
        // void disableRender();
        void loop();

        private:
        LCD *m_display;
        Data::MainParam_t m_mainData;
        Data::SelectedItem_t m_selectedItem;
        Motor * m_motor;
        Button* m_up,*m_down,*m_plus,*m_minus,*m_enter;
        Data::Page_t m_currentPage;
        Button *m_buttons[MAX_BUTTON_NUM];
        uint16_t m_movementParam[5];
};