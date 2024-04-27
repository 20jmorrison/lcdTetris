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

#include <LiquidCrystal.h>
#include <String.h>
#include "Joystick.h"

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
Joystick joystick;


uint8_t L[8] = {
  0b00010,
  0b00010,
  0b00011,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
};


void setup() {
  Serial.begin(BAUD);

  lcd.begin(16, 2);
  lcd.createChar(0, L);
  lcd.clear();
  lcd.write((uint8_t)0);
  
  joystick.start();
}

void loop() {
  DIRECTION currDirection = joystick.getJoystickDirection();
  joystick.printJoystickDirection(currDirection);
  delay(1000);
  // shiftChar(L);
  // lcd.createChar(0, L);
  // lcd.clear();
  // lcd.write((uint8_t)0);
  //Serial.println("hi");
  //Serial.println(joystick.getJoystickDirection());
}

void shiftChar(uint8_t bits[]) {
  for (int i = 7; i >= 0; i--) {
    bits[i] = (bits[i] << 1) | (bits[i] >> 4);
  }
}
