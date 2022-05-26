#pragma once
// #include "manager.h"
#include "data.h"
#include <U8g2lib.h>
#define LCDWidth                        m_lcd->getDisplayWidth()
#define ALIGN_CENTER(t)                 ((LCDWidth - (m_lcd->getStrWidth(t))) / 2)
#define ALIGN_RIGHT(t)                  (LCDWidth -  m_lcd->getStrWidth(t))
#define ALIGN_LEFT                      0
const char str0[]  = "ASEP";
const char str1[]  = "Awesome Stepper";
const char str2[]  = "Enabler Project v1.0";

class LCD{

    public:
    
    LCD(U8G2_SSD1306_128X32_UNIVISION_1_HW_I2C *lcd);
    void setup();
    void drawSplashScreen();
    void drawMainPage( Data::MainParam_t data);
    void drawSavedScreen();
    private:

    U8G2_SSD1306_128X32_UNIVISION_1_HW_I2C *m_lcd;
};