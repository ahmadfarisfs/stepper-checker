#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "config.h"
#include <U8g2lib.h>
#include "btn.h"
#include "motor.h"
#include "nonstd.h"
#include "manager.h"
#include "lcd.h"
#include "bzr.h"
#include "blinky.h"
#include "adv.h"
Button moveR(BTN_MOVE_R_PIN, true);
Button moveL(BTN_MOVE_L_PIN, true);
Button speedUp(BTN_SPEED_UP_PIN, true);
Button speedDown(BTN_SPEED_DOWN_PIN, true);
Button enter(BTN_EN_PIN, true);
FastAccelStepperEngine engine = FastAccelStepperEngine();
FastAccelStepper *stepper = NULL;

//PrimitiveMotor motor(EN_PIN, STEP_PIN, DIR_PIN);
Buzzer buzzer(BZR_PIN);
U8G2_SSD1306_128X32_UNIVISION_1_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

LCD display(&u8g2);
EnhancedMotor motor(EN_PIN, STEP_PIN, DIR_PIN, &engine, stepper);
StepperTesterManager manager(&moveR, &moveL, &speedDown, &speedUp, &enter, &motor, &display, &buzzer);
Blinky status(STATUS_LED_PIN);
void setup()
{
  Serial.begin(115200);
  Serial.println("=BEGIN=");
  status.setDuration(500);
  manager.setup();
}

void loop()
{
  manager.loop();
  status.loop();
}
