// LCD Pin Descriptions
// --------------------
//
// VSS ----- Ground
// VDD ----- 5v Input
// V0 ------ Contrast Control
// RS ------ Register/Select
// RW ------ Read/Write
// EN ------- Enable
// D4 ------ Data Bus
// D5 ------ Data Bus
// D6 ------ Data Bus
// D7 ------ Data Bus
// A ------- Backlight 5v Input
// K ------- Backlight Ground


// Arduino Nano Every Pinout
// -------------------------
// RS ------ 21
// EN ------ 20
// D4 ------ 19
// D5 ------ 18
// D6 ------ 17
// D7 ------ 16


#define BAUD 9600
#define RS 21
#define EN 20
#define D4 9
#define D5 10
#define D6 11
#define D7 12

#include "Joystick.h"
#include "LCD.h"

LCD lcd(RS, EN, D4, D5, D6, D7);
Joystick joystick;

void setup() {
  Serial.begin(BAUD);
  
  lcd.configure();
  joystick.configure();
}

void loop() {
  DIRECTION currDirection = joystick.getJoystickDirection();
  joystick.printJoystickDirection(currDirection);
  delay(1000);
  lcd.shiftDown();
}

