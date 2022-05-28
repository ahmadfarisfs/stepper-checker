#pragma once
#include <Arduino.h>
// #include <U8g2lib.h>
#include "btn.h"
#include "motor.h"
#include "data.h"
#include "lcd.h"
#include "bzr.h"
#define MAX_BUTTON_NUM 5
class StepperTesterManager
{

public:
    StepperTesterManager(Button *up, Button *down, Button *plus, Button *minus, Button *enter, Motor *motor, LCD *lcd, Buzzer * bzr);
    void setup();
    void loop();

private:
unsigned long m_lastUpdatedScreenTs;
    void updateItem(Data::ScreenSelectedItem_e selectedID, int8_t changes);
    LCD *m_display;
    Data::ScreenSelectedItem_e m_selectedItem;
    Motor *m_motor;
    Button *m_up, *m_down, *m_plus, *m_minus, *m_enter;
    Data::ScreenPage_e m_currentPage;
    Button *m_buttons[MAX_BUTTON_NUM];
    Buzzer *m_buzzer;
};