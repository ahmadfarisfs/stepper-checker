#include "lcd.h"
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
LCD::LCD(SSD1306AsciiWire *lcd)
{
    m_lcd = lcd;
    m_currentScreen = Data::ScreenPage_e::INITIAL;
}

void LCD::drawSplashScreen()
{
    if (m_currentScreen != Data::ScreenPage_e::SplashScreen)
    {
        m_lcd->clear();
        m_lcd->setCol(ALIGN_CENTER(str0));
        m_lcd->println(str0);
        m_lcd->setCol(ALIGN_CENTER(str1));
        m_lcd->println(str1);
        m_lcd->setCol(ALIGN_CENTER(str2));
        m_lcd->println(str2);
        m_currentScreen = Data::ScreenPage_e::SplashScreen;
    }

    // awesome splash screen!
    // m_lcd->firstPage();
    // do
    // {
    //     m_lcd->setFont(u8g2_font_tenstamps_mf); // 12 pixel
    //     m_lcd->drawStr(ALIGN_CENTER(str0), 12, str0);
    //     m_lcd->setFont(u8g2_font_5x7_tr); // 6 pixel
    //     m_lcd->drawStr(ALIGN_CENTER(str1), 23, str1);
    //     m_lcd->drawStr(ALIGN_CENTER(str2), 31, str2);
    // } while (m_lcd->nextPage());
};
void LCD::setup()
{
    Wire.begin();
    Wire.setClock(400000L);
    m_lcd->begin(&Adafruit128x32, I2C_ADDRESS);
    m_lcd->setFont(Adafruit5x7);
    // upcast to parent class
    // U8G2_SSD1306_128X32_UNIVISION_1_HW_I2C(U8G2_R0, U8X8_PIN_NONE);

    // m_lcd->begin();
};
void LCD::drawMainPage(Data::ScreenMainParam_t data)
{

    if (data != m_prevData)
    {

        char str[4][22];
        char symbChar[4];
        char speedChar[10];
        sprintf(str[0], " Speed : %u pps", data.moveParam.speedPps);
        sprintf(str[1], " RampUp: %u ms", data.moveParam.rampUpMs);
        sprintf(str[2], " RampDw: %u ms", data.moveParam.rampDownMs);
        sprintf(str[3], " Enable: %s", data.isEnabled ? "TRUE" : "FALSE");
        char symb, dirSym0, dirSym1;
        switch (data.state)
        {
        case Data::MotorState_e::RampingDown:
            symb = '\\';
            break;
        case Data::MotorState_e::RampingUp:
            symb = '/';
            break;
        case Data::MotorState_e::ConstantSpeed:
            symb = '=';
            break;
        default:
            symb = ' ';
            break;
        }

        if (data.state != Data::MotorState_e::Idle)
        {
            if (data.direction == Data::MotorDirection_e::Forward)
            {
                dirSym0 = ' ';
                dirSym1 = '>';
            }
            else
            {
                dirSym0 = '<';
                dirSym1 = ' ';
            }
        }
        else
        {
            dirSym0 = ' ';
            dirSym1 = ' ';
        }

        sprintf(symbChar, "%c%c%c", dirSym0, symb, dirSym1);
        sprintf(speedChar, "%u", data.currentSpeed);


        m_lcd->clear();
        for (uint8_t i = 0; i < 4; i++)
        {
            m_lcd->println(str[i]);
        }
        m_lcd->setCursor(ALIGN_RIGHT(symbChar), 2);
        m_lcd->println(symbChar);
        m_lcd->setCursor(ALIGN_RIGHT(speedChar), 3);
        m_lcd->println(speedChar);
        m_lcd->setCursor(0, data.selectedItem);
        m_lcd->print(F(">"));
        // m_lcd->setFont(u8g2_font_5x7_tr); // 6 pixel
        // m_lcd->drawStr(9, 8, str[0]);
        // m_lcd->drawStr(9, 8+8, str[1]);
        // m_lcd->drawStr(9, 8+8+8, str[2]);
        // m_lcd->drawStr(9, 8+8+8+8, str[3]);
        // m_lcd->drawStr(0,8+data.selectedItem*8,">");
        // m_lcd->setFont(u8g2_font_bytesize_tf );
        // m_lcd->drawStr(ALIGN_RIGHT(symbChar),12, symbChar);
        // m_lcd->drawStr(ALIGN_RIGHT(speedChar),29, speedChar);
        m_prevData = data;
    }
    // } while (m_lcd->nextPage());
};
void LCD::drawSavedScreen()
{
    if (m_currentScreen != Data::ScreenPage_e::SavedScreen)
    {
        m_lcd->clear();
        m_lcd->println(F("SAVED"));
        m_currentScreen = Data::ScreenPage_e::SavedScreen;
    }
    //    m_lcd->firstPage();
    //     do
    //     {
    //         m_lcd->drawButtonUTF8(5, 20, U8G2_BTN_INV, m_lcd->getDisplayWidth()-5*2,  5,  2, "Config Saved!" );
    //     } while (m_lcd->nextPage());
};