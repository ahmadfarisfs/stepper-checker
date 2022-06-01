#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "config.h"
// #include <U8g2lib.h>
#include "btn.h"
#include "binder.h"
#include "motor.h"
// #include "nonstd.h"
#include "manager.h"
#include "lcd.h"
#include "bzr.h"
#include "blinky.h"
#include "adv.h"
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
Button moveR(BTN_MOVE_R_PIN, true);
Button moveL(BTN_MOVE_L_PIN, true);
Button speedUp(BTN_SPEED_UP_PIN, true);
Button speedDown(BTN_SPEED_DOWN_PIN, true);
Button enter(BTN_EN_PIN, true);
FastAccelStepperEngine engine = FastAccelStepperEngine();
FastAccelStepper *stepper = NULL;

Buzzer buzzer(BZR_PIN);
SSD1306AsciiWire ssdDisplay;
LCD display(&ssdDisplay);
EnhancedMotor motor(EN_PIN, STEP_PIN, DIR_PIN, &engine, stepper);
StepperTesterManager manager(&moveR, &moveL, &speedDown, &speedUp, &enter, &motor, &display, &buzzer);
Blinky status(STATUS_LED_PIN);

void setup()
{
  CallBinder::setManObj(&manager);
  Serial.begin(115200);
  Serial.println("=BEGIN=");
  status.setDuration(200);
  manager.setup(&CallBinder::onStartLeft,&CallBinder::onStopMotor,&CallBinder::onStartRight,
  &CallBinder::onPlusOne,&CallBinder::onPlusTen,&CallBinder::onMinusOne,&CallBinder::onMinusTen,
  &CallBinder::onEnter,&CallBinder::onSave
  );
}

void loop()
{
  manager.loop();
  status.loop();
}
// #include <SPI.h>
// #include <Wire.h>
// #include <Arduino.h>
// #include <Tiny4kOLED.h>

// 4264 bytes program, 101 bytes dynamic memory
// 348ms to fill the screen
// #include <Tiny4kOLED_Wire.h>

// 3920 bytes program, 80 bytes dynamic memory
// 142ms to fill the screen
//#include <Tiny4kOLED_TinyWireM.h>

// 3672 bytes program, 60 bytes dynamic memory
// 56ms to fill the screen
// #include <Tiny4kOLED_tiny-i2c.h>

// 3622 bytes program, 60 bytes dynamic memory
// 45ms to fill the screen
// #include <Tiny4kOLED_bitbang.h>

// unsigned long lastTime = 0L;

// void setup() {
//   Wire.setClock(3400000 );
//   // Test by writing to the entire memory space of the SSD1306
//   oled.begin(128, 32, sizeof(tiny4koled_init_128x32br), tiny4koled_init_128x32br);
//   oled.clear();
//   oled.setFont(FONT8X16);
//   oled.on();
//   lastTime = millis();
// }

// uint8_t b = 0;
// void loop() {
//   oled.fill(b);
//   if (b==255) {
//     unsigned long thisTime = millis();
//     oled.setCursor(0,0);
//     oled.println((thisTime-lastTime)>>8, DEC);
//     delay(4000);
//     lastTime = millis();
//   }
//   b++;
// }