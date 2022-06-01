#pragma once
// #include "manager.h"
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include "data.h"
#define I2C_ADDRESS 0x3C
// #include <U8g2lib.h>
#define LCDWidth                        128
#define ALIGN_CENTER(t)                 ((LCDWidth - (m_lcd->strWidth(t))) / 2)
#define ALIGN_RIGHT(t)                  (LCDWidth -  m_lcd->strWidth(t))
#define ALIGN_LEFT                      0
const char str0[]  = "ASEP";
const char str1[]  = "Awesome Stepper";
const char str2[]  = "Enabler Project v1.0";

class LCD{

    public:
    
    LCD(SSD1306AsciiWire *lcd);
    void setup();
    void drawSplashScreen();
    void drawMainPage( Data::ScreenMainParam_t data);
    void drawSavedScreen();
    private:
    bool m_isDrawn;
    Data::ScreenPage_e m_currentScreen;
    Data::ScreenMainParam_t m_prevData;
    SSD1306AsciiWire *m_lcd;
};