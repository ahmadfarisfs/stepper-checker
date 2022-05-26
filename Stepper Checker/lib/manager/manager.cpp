#include "manager.h"
#include "btn.h"
#include "motor.h"
#include "lcd.h"
StepperTesterManager::StepperTesterManager(Button *up, Button *down, Button *plus, Button *minus, Button *enter, Motor *motor,LCD *lcd)
{
    m_display =lcd;
    // m_enabled = false;
    m_up = up;
    m_down = down;
    m_plus = plus;
    m_minus = minus;
    m_enter = enter;
    m_motor = motor;
    m_currentPage = Data::Page_t::SplashScreen;
    m_buttons[0] = m_up;
    m_buttons[1] = m_down;
    m_buttons[2] = m_plus;
    m_buttons[3] = m_minus;
    m_buttons[4] = m_enter;
    
};

void StepperTesterManager::setup()
{
    m_display->setup();
    m_motor->setup();
    m_motor->setMoveParam(1000, 1000, 1000); // default move param
    for (uint8_t i = 0; i < MAX_BUTTON_NUM; i++)
    {
        m_buttons[i]->setup(1000, 100, 25);
    }
    m_up->setCallback(Button::EventType_e::ButtonDown, [&](void)
                      {
                          Serial.println("RDown");

                          switch (m_currentPage)
                          {
                          case Data::Page_t::SplashScreen:
                              m_currentPage = Data::Page_t::MainScreen;
                              break;
                          case Data::Page_t::MainScreen:
                              // tell controller to move
                              m_motor->moveStart(Motor::MovementType_e::Forward, micros());
                              break;
                          case Data::Page_t::SavedScreen:
                              m_currentPage = Data::Page_t::MainScreen;
                              break;

                          default:
                              break;
                          } });

    m_up->setCallback(Button::EventType_e::ButtonUp, [&](void)
                      { Serial.println("RUp"); 
        if(m_currentPage == Data::Page_t::MainScreen){
        
                      m_motor->moveStop(micros());
              } });

    m_down->setCallback(Button::EventType_e::ButtonDown, [&](void)
                        {
            switch (m_currentPage)
            {
            case Data::Page_t::SplashScreen:
                m_currentPage = Data::Page_t::MainScreen;
                break;
            case Data::Page_t::MainScreen:
                //tell controller to move
                m_motor->moveStart(Motor::MovementType_e::Reverse,micros());
                break;
            case Data::Page_t::SavedScreen:
                m_currentPage = Data::Page_t::MainScreen;
                break;

            default:
                break;
            } });

    m_down->setCallback(Button::EventType_e::ButtonUp, [&](void)
                        {
                            Serial.println("LUp");

                            if (m_currentPage == Data::Page_t::MainScreen)
                            {

                                m_motor->moveStop(micros());
                            } });

    m_plus->setCallback(Button::EventType_e::ButtonDown, [&](void)
                        {
                        // add by 1
                        Serial.println("+down"); 
                          if(m_currentPage == Data::Page_t::MainScreen){
                              m_movementParam[m_selectedItem]++;
      }else{
          m_currentPage = Data::Page_t::MainScreen;
      } });
    m_plus->setCallback(Button::EventType_e::ButtonLongPressInterval, [&](void)
                        {
                            // add by 10
                            Serial.println("+lpint");
                            if (m_currentPage == Data::Page_t::MainScreen)
                            {
                                m_movementParam[m_selectedItem] += 10;
                            }
                            else
                            {
                                m_currentPage = Data::Page_t::MainScreen;
                            } });

    m_minus->setCallback(Button::EventType_e::ButtonDown, [&](void)
                         {
                             // reduce by 1
                             Serial.println("-down");
                             if (m_currentPage == Data::Page_t::MainScreen)
                             {
                                 // handle overflow
                                 m_movementParam[m_selectedItem]--;
                             }
                             else
                             {
                                 m_currentPage = Data::Page_t::MainScreen;
                             } });
    m_minus->setCallback(Button::EventType_e::ButtonLongPressInterval, [&](void)
                         {
                          // reduce by 10
                          if(m_currentPage == Data::Page_t::MainScreen){
                              m_movementParam[m_selectedItem]-=10;
      }else{
          m_currentPage = Data::Page_t::MainScreen;
      }
                          Serial.println("-lpint"); });

    m_enter->setCallback(Button::EventType_e::ButtonDown, [&](void)
                         {
    // next item
     Serial.println("entdw"); 
      if(m_currentPage == Data::Page_t::MainScreen){
          m_selectedItem = (Data::SelectedItem_t)((uint8_t)m_selectedItem+1);
          m_selectedItem =(Data::SelectedItem_t)((uint8_t)m_selectedItem%4); 
      }else{
          m_currentPage = Data::Page_t::MainScreen;
      } });

    m_enter->setCallback(Button::EventType_e::ButtonLongPress, [&](void)
                         {
    //TODO:save to config
     Serial.println("entlp"); });

     m_currentPage = Data::Page_t::SplashScreen;
}


void StepperTesterManager::loop()
{
    if (m_motor->getStatus() == Motor::MovementStatus_e::Idle)
    {
        switch (m_currentPage)
        {
        case Data::Page_t::SplashScreen :
            m_display->drawSplashScreen();
            break;
        case Data::Page_t::MainScreen:
        Data::MainParam_t param;
        param.rampDwMs = m_movementParam[(uint8_t)Data::SelectedItem_t::RampDown];
        param.rampUpMs = m_movementParam[(uint8_t)Data::SelectedItem_t::RampUp];
        param.speedPps = m_movementParam[(uint8_t)Data::SelectedItem_t::Speed];
        param.selectedItem = m_selectedItem;
        param.isEnabled = m_movementParam[(uint8_t)Data::SelectedItem_t::MotorEnable];
        m_display->drawMainPage(param);
        
        break;
        case Data::Page_t::SavedScreen:
        m_display->drawSavedScreen();
        break;

        default:
            break;
        }
    }

    // keyboard area
    for (uint8_t i = 0; i < MAX_BUTTON_NUM; i++)
    {
        m_buttons[i]->loop();
    }

    // motor area
    m_motor->loop(micros());
}