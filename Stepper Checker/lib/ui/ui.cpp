#include "ui.h"
// #include "U8g2lib.h"
#include "btn.h"
UIManager::UIManager(Button *up, Button *down, Button *plus, Button *minus, Button *enter)
{
    m_enabled = false;
    m_up = up;
    m_down = down;
    m_plus = plus;
    m_minus = minus;
    m_enter = enter;
    m_currentPage = Page_t::SplashScreen;
};

void UIManager::setup()
{
    m_up->setCallback(Button::EventType_e::ButtonDown, [](void)
                      { Serial.println("RDown"); });

    m_up->setCallback(Button::EventType_e::ButtonUp, [](void)
                      { Serial.println("RUp"); });

    m_down->setCallback(Button::EventType_e::ButtonDown, [&](void)
                        {
            switch (m_currentPage)
            {
            case SplashScreen:
                m_currentPage = MainScreen;
                break;
            case MainScreen:
                //tell controller to move
                break;
            case SavedScreen:
                m_currentPage = MainScreen;
                break;

            default:
                break;
            } });

    m_down->setCallback(Button::EventType_e::ButtonUp, [](void)
                        { Serial.println("LUp"); });

    m_plus->setCallback(Button::EventType_e::ButtonDown, [](void)
                        {
                        // add by 1
                        Serial.println("+down"); });
    m_plus->setCallback(Button::EventType_e::ButtonLongPressInterval, [](void)
                        {
                        // add by 10
                        Serial.println("+lpint"); });

    m_minus->setCallback(Button::EventType_e::ButtonDown, [](void)
                         {
                          // reduce by 1
                          Serial.println("-down"); });
    m_minus->setCallback(Button::EventType_e::ButtonLongPressInterval, [](void)
                         {
                          // reduce by 10
                          Serial.println("-lpint"); });

    m_enter->setCallback(Button::EventType_e::ButtonDown, [](void)
                         {
    //next item
     Serial.println("entdw"); });

    m_enter->setCallback(Button::EventType_e::ButtonLongPress, [](void)
                         {
    //save to config
     Serial.println("entlp"); });
}
void UIManager::enableRender()
{
    m_enabled = true;
};

void UIManager::disableRender()
{
    m_enabled = false;
};

void UIManager::setPage(Page_t page)
{
    m_currentPage = page;
};

// void UIManager::setParam(const MainParam_t *param)
// {
//         m_uiState = *param;
// }

// void UIManager::getParam(MainParam_t *param)
// {
//         param = &m_uiState;
// }

void UIManager::loop()
{
    if (m_enabled)
    {
        // u8g2.
    }

    // keyboard area
}