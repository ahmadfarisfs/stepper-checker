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
void LCD::drawMainPage(Data::MainParam_t data){
    char str[64];
    sprintf(str, "%d %d %d %d", data.selectedItem,data.rampUpMs,data.rampDwMs,data.speedPps);
   m_lcd->firstPage();
    do
    {
        m_lcd->setFont(u8g2_font_5x7_tr); // 6 pixel
        m_lcd->drawStr(0, 12, str);
        m_lcd->drawStr(ALIGN_CENTER(str1), 23, str1);
        m_lcd->drawStr(ALIGN_CENTER(str2), 31, str2);
    } while (m_lcd->nextPage());
};
void LCD::drawSavedScreen(){

};