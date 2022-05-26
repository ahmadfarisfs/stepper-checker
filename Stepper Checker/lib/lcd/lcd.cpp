#include "lcd.h"
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
LCD::LCD(U8G2_SSD1306_128X32_UNIVISION_1_HW_I2C *lcd)
{
     m_lcd = lcd;
}

void LCD::drawSplashScreen()
{
    // awesome splash screen!
    m_lcd->firstPage();
    do
    {
        m_lcd->setFont(u8g2_font_tenstamps_mf); // 12 pixel
        m_lcd->drawStr(ALIGN_CENTER(str0), 12, str0);
        m_lcd->setFont(u8g2_font_5x7_tr); // 6 pixel
        m_lcd->drawStr(ALIGN_CENTER(str1), 23, str1);
        m_lcd->drawStr(ALIGN_CENTER(str2), 31, str2);
    } while (m_lcd->nextPage());
};
void LCD::setup()
{
    // upcast to parent class
   //U8G2_SSD1306_128X32_UNIVISION_1_HW_I2C(U8G2_R0, U8X8_PIN_NONE);
    m_lcd->begin();
};
void LCD::drawMainPage(Data::ScreenMainParam_t data){
    char str[4][22];
    char symbChar[4];
    char speedChar[10];
    sprintf(str[0], "Speed : %u pps", data.moveParam.speedPps );
    sprintf(str[1], "RampUp: %u ms", data.moveParam.rampUpMs );
    sprintf(str[2], "RampDw: %u ms", data.moveParam.rampDownMs );
    sprintf(str[3], "Enable: %s", data.isEnabled ? "TRUE":"FALSE" );
    char symb,dirSym0,dirSym1;
    switch (data.state)
    {
    case Data::MotorState_e::RampingDown:
        symb='\\';
        break;
    case Data::MotorState_e::RampingUp:
        symb='/';
        break;
    case Data::MotorState_e::ConstantSpeed:
        symb='=';
        break;
    default:
        symb=' ';
        break;
    }

    if(data.state != Data::MotorState_e::Idle){
    if(data.direction == Data::MotorDirection_e::Forward){
        dirSym0 = ' ';
        dirSym1 = '>';
    }else{
        dirSym0 = '<';
        dirSym1 = ' ';
    }}else{
        dirSym0 = ' ';
        dirSym1 = ' ';
        
    }

    sprintf(symbChar, "%c%c%c", dirSym0,symb,dirSym1 );
    sprintf(speedChar, "%u", data.currentSpeed );
    
    m_lcd->firstPage();
    do
    {
        m_lcd->setFont(u8g2_font_5x7_tr); // 6 pixel
        m_lcd->drawStr(9, 8, str[0]);
        m_lcd->drawStr(9, 8+8, str[1]);
        m_lcd->drawStr(9, 8+8+8, str[2]);
        m_lcd->drawStr(9, 8+8+8+8, str[3]);
        m_lcd->drawStr(0,8+data.selectedItem*8,">");
        m_lcd->setFont(u8g2_font_bytesize_tf );
        m_lcd->drawStr(ALIGN_RIGHT(symbChar),12, symbChar);
        m_lcd->drawStr(ALIGN_RIGHT(speedChar),29, speedChar);
        
    } while (m_lcd->nextPage());
};
void LCD::drawSavedScreen(){
   m_lcd->firstPage();
    do
    {
        m_lcd->drawButtonUTF8(5, 20, U8G2_BTN_INV, m_lcd->getDisplayWidth()-5*2,  5,  2, "Config Saved!" );
    } while (m_lcd->nextPage());
};