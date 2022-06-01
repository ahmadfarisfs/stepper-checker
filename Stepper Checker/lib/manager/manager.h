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
    StepperTesterManager(Button *up, Button *down, Button *plus, Button *minus, Button *enter, IMotor *motor, LCD *lcd, Buzzer *bzr);
    void setup(void (*onStartLeft)(void),void (*onStopMotor)(void),void (*onStartRight)(void),
void (*onPlusOne)(void),void (*onPlusTen)(void),void (*onMinusOne)(void),void (*onMinusTen)(void),void (*onEnter)(void),
void (*onSave)(void));
    void loop();
    void onStartMotor(Data::MotorDirection_e dir);
    void onStopMotor();
    void onChangeVars(int8_t delta);
    void onEnter();
    void onSave();

private:
unsigned long m_lastUpdatedScreenTs;
    void updateItem(Data::ScreenSelectedItem_e selectedID, int8_t changes);
    LCD *m_display;
    Data::ScreenSelectedItem_e m_selectedItem;
    IMotor *m_motor;
    Button *m_up, *m_down, *m_plus, *m_minus, *m_enter;
    Data::ScreenPage_e m_currentPage;
    Button *m_buttons[MAX_BUTTON_NUM];
    Buzzer *m_buzzer;
};