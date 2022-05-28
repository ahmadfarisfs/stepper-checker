#include "manager.h"
#include "btn.h"
#include "motor.h"
#include "lcd.h"
#include <EEPROM.h>
StepperTesterManager::StepperTesterManager(Button *up, Button *down, Button *plus, Button *minus, Button *enter, Motor *motor, LCD *lcd,Buzzer * bzr)
{
    m_display = lcd;
    m_up = up;
    m_down = down;
    m_plus = plus;
    m_minus = minus;
    m_enter = enter;
    m_motor = motor;
    m_currentPage = Data::ScreenPage_e::SplashScreen;
    m_buttons[0] = m_up;
    m_buttons[1] = m_down;
    m_buttons[2] = m_plus;
    m_buttons[3] = m_minus;
    m_buttons[4] = m_enter;
    m_lastUpdatedScreenTs = 0;
    m_buzzer = bzr;
};

void StepperTesterManager::setup()
{
    m_display->setup();
    m_motor->setup();
    m_buzzer->setup();
    m_buzzer->buzz(1000);
    Data::MotorMoveParam_e paramMotor;
    EEPROM.get(0,paramMotor);

    m_motor->setMoveParam(paramMotor); // default move param
    for (uint8_t i = 0; i < MAX_BUTTON_NUM; i++)
    {
        m_buttons[i]->setup(1000, 50, 25);
    }
    m_up->setCallback(Button::EventType_e::ButtonDown, [&](void)
                      {

                          if(m_currentPage == Data::ScreenPage_e::MainScreen){
                              m_buzzer->buzz(500);
    
                            m_motor->moveStart(Data::MotorDirection_e::Forward, micros());
                          }else{
                            m_currentPage = Data::ScreenPage_e::MainScreen;
                            m_buzzer->buzz(50);
                          }
                          });

    m_up->setCallback(Button::EventType_e::ButtonUp, [&](void){ 
        if(m_currentPage == Data::ScreenPage_e::MainScreen){
            m_buzzer->buzz(500);
            m_motor->moveStop(micros());
        }
        });

    m_down->setCallback(Button::EventType_e::ButtonDown, [&](void)
                        {
             if(m_currentPage == Data::ScreenPage_e::MainScreen){
                 m_buzzer->buzz(500);
                            m_motor->moveStart(Data::MotorDirection_e::Reverse, micros());
                          }else{
                            m_currentPage = Data::ScreenPage_e::MainScreen;
                            m_buzzer->buzz(50);
                          } });

    m_down->setCallback(Button::EventType_e::ButtonUp, [&](void)
                        {
                            if (m_currentPage == Data::ScreenPage_e::MainScreen)
                            {
                                m_buzzer->buzz(500);
                                m_motor->moveStop(micros());
                            } });

    m_plus->setCallback(Button::EventType_e::ButtonDown, [&](void)
                        { 
                            m_buzzer->buzz(50);
                          if(m_currentPage == Data::ScreenPage_e::MainScreen){
                              updateItem(m_selectedItem,1);
                            }else{
                                m_currentPage = Data::ScreenPage_e::MainScreen;
                            } });
    m_plus->setCallback(Button::EventType_e::ButtonLongPressInterval, [&](void)
                        {
                                                       

                            // add by 10
                            if (m_currentPage == Data::ScreenPage_e::MainScreen)
                            {
                                 m_buzzer->buzz(20);
                               updateItem(m_selectedItem,10);
                            }
                            else
                            {
                                m_currentPage = Data::ScreenPage_e::MainScreen;
                            } });

    m_minus->setCallback(Button::EventType_e::ButtonDown, [&](void)
                         {m_buzzer->buzz(50);
                             if (m_currentPage == Data::ScreenPage_e::MainScreen)
                             {
                                 // handle overflow
                                  
                                 updateItem(m_selectedItem,-1);
                             }
                             else
                             {
                                 m_currentPage = Data::ScreenPage_e::MainScreen;
                             } });
    m_minus->setCallback(Button::EventType_e::ButtonLongPressInterval, [&](void)
                         {
                          // reduce by 10
                          if(m_currentPage == Data::ScreenPage_e::MainScreen){
                               m_buzzer->buzz(20);
                              updateItem(m_selectedItem,-10);
      }else{
          m_currentPage = Data::ScreenPage_e::MainScreen;
      }
});

    m_enter->setCallback(Button::EventType_e::ButtonDown, [&](void)
                         {
    // next item
     m_buzzer->buzz(50);
      if(m_currentPage == Data::ScreenPage_e::MainScreen){
          m_selectedItem = (Data::ScreenSelectedItem_e)((uint8_t)m_selectedItem+1);
          m_selectedItem =(Data::ScreenSelectedItem_e)((uint8_t)m_selectedItem%4); 
      }else{
          m_currentPage = Data::ScreenPage_e::MainScreen;
      } });

    m_enter->setCallback(Button::EventType_e::ButtonLongPress, [&](void)
                         {
                            if(m_currentPage == Data::ScreenPage_e::MainScreen){
                                m_currentPage = Data::ScreenPage_e::SavedScreen;
                            }
                             m_buzzer->buzz(1000);
    EEPROM.put(0,m_motor->getMoveParam());
     });
    
    m_currentPage = Data::ScreenPage_e::SplashScreen;
}
void StepperTesterManager::updateItem(Data::ScreenSelectedItem_e selectedID, int8_t changes){
    
    switch (selectedID)
    {
    case Data::ScreenSelectedItem_e::Speed :
        {Data::MotorMoveParam_e param= m_motor->getMoveParam();
        param.speedPps = max( (int32_t)param.speedPps + changes,0); 
        m_motor->setMoveParam(param);   
        break;}
    case Data::ScreenSelectedItem_e::RampDown :
        {Data::MotorMoveParam_e param= m_motor->getMoveParam();
        param.rampDownMs = max((int32_t)param.rampDownMs + changes,0); 
        m_motor->setMoveParam(param);   
        break;}
    case Data::ScreenSelectedItem_e::RampUp :
        {Data::MotorMoveParam_e param= m_motor->getMoveParam();
        param.rampUpMs = max((int32_t)param.rampUpMs + changes,0); 
        m_motor->setMoveParam(param);   
        break;}
    case Data::ScreenSelectedItem_e::MotorEnable :
        {if(changes > 0){
            m_motor->setArmed(true);
        }else{
            m_motor->setArmed(false);
        }
        break;}
    
    default:
        break;
    }
};
void StepperTesterManager::loop()
{   unsigned long currentTs = millis();
    if(m_lastUpdatedScreenTs + 250 < currentTs || m_motor->getState() == Data::MotorState_e::Idle)
    {
        switch (m_currentPage)
        {
        case Data::ScreenPage_e::SplashScreen:
           { m_display->drawSplashScreen();
            break;}
        case Data::ScreenPage_e::MainScreen:
            {Data::ScreenMainParam_t paramLcd;
            Data::MotorState_e stateMotor = m_motor->getState();
            Data::MotorMoveParam_e motorParam = m_motor->getMoveParam();
            paramLcd.direction = m_motor->getCurrentDir();
            paramLcd.isEnabled = m_motor->isArmed();
            paramLcd.currentSpeed = m_motor->getCurrentSpeedPps();
            paramLcd.moveParam = motorParam;
            paramLcd.selectedItem = m_selectedItem;
            paramLcd.state = stateMotor;
            m_display->drawMainPage(paramLcd);

            break;}
        case Data::ScreenPage_e::SavedScreen:
            {m_display->drawSavedScreen();
            break;}

        default:
            break;
        }
        m_lastUpdatedScreenTs = currentTs;
    }

    // keyboard area
    for (uint8_t i = 0; i < MAX_BUTTON_NUM; i++)
    {
        m_buttons[i]->loop();
    }

    // motor area
    m_motor->loop(micros());
    m_buzzer->loop();
}