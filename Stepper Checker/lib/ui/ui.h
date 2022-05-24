#pragma once
#include <Arduino.h>
#include <U8g2lib.h>
#include "btn.h"
class UIManager{
        
    public:
        enum Page_t{
            SplashScreen,
            MainScreen,
            SavedScreen
        };
        enum SelectedItem_t{
            Speed=0,
            RampUp=1,
            RampDown=2,
        };
        enum EventType_e {
            OnMoveStartFwd,
            OnMoveStartRev,
            OnMoveStop,
        };
        enum ParamType_t{
            
        };
        // enum RunningState_t{
        //     Idle=0,
        //     MovingR=1,
        //     MovingL=2,
        // };
        // struct MainParam_t{
        //     uint32_t speedPps;
        //     uint16_t rampUpMs;
        //     uint16_t rampDwMs;
        //     SelectedItem_t selectedItem;
        //     RunningState_t runState;
        //     uint8_t saveProgress;
        // };
        UIManager( Button *up, Button*down,  Button*plus,  Button*minus, Button*enter);
        void setup();
        void onEvent();        
        void enableRender();
        void disableRender();
        void setPage(Page_t page);
        void setMoveCallback();
        void setParamChangeCallback(ParamType_t param, int8_t deltaVal);
        // void setParam(const MainParam_t *param);
        // void getParam(MainParam_t *param);
        void loop();

        private:
        Button* m_up,*m_down,*m_plus,*m_minus,*m_enter;
        // U8G2_SSD1306_128X32_UNIVISION_1_HW_I2C m_lcd;
        // MainParam_t m_uiState;
        bool m_enabled;
        Page_t m_currentPage;
        Button *buttons[];// = {&moveR, &moveL, &speedUp, &speedDown, &enter};

};