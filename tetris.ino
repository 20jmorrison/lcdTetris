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
#include <WiiChuck.h>
#include "Sprites.h"

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
Accessory nunchuck;

enum DIRECTION {
  LEFT,
  RIGHT,
  UP,
  DOWN,
  CENTER
};

enum BUTTON {
  C,
  Z,
  NONE
};

void setup() {
  Serial.begin(BAUD);

  lcd.createChar(0, L);
  lcd.begin(16, 2);
  lcd.write((uint8_t)0);

  nunchuck.begin();
  nunchuck.type = NUNCHUCK;
}

void loop() {
  //BUTTON currButton = getJoystickButtons();
  //DIRECTION currDirection = getJoystickDirection();

}


DIRECTION getJoystickDirection() {
  nunchuck.readData();

  uint8_t xPos = nunchuck.values[0];
  uint8_t yPos = nunchuck.values[1];

  if (xPos < 75) {
    return LEFT;
  } else if (xPos > 175) {
    return RIGHT;
  } else if (yPos < 75) {
    return DOWN;
  } else if (yPos > 175) {
    return UP;
  } else {
    return CENTER;
  }
}

BUTTON getJoystickButtons() {
  nunchuck.readData();

  uint8_t cButton = nunchuck.values[11];
  uint8_t zButton = nunchuck.values[10];

  if (cButton == 255) {
    return C;
  } else if (zButton == 255) {
    return Z;
  } else {
    return NONE;
  }
}

void printJoystickButtons(BUTTON button) {
  switch (button) {
    case 0:
      {
        Serial.println("C");
        break;
      }
    case 1:
      {
        Serial.println("Z");
        break;
      }
    case 2:
      {
        Serial.println("NO_PRESS");
        break;
      }
    default:
      {
        break;
      }
  }
}


void printJoystickDirection(DIRECTION direction) {
  switch (direction) {
    case 0:
      {
        Serial.println("LEFT");
        break;
      }
    case 1:
      {
        Serial.println("RIGHT");
        break;
      }
    case 2:
      {
        Serial.println("UP");
        break;
      }
    case 3:
      {
        Serial.println("DOWN");
        break;
      }
    case 4:
      {
        Serial.println("CENTER");
        break;
      }
    default:
      {
        break;
      }
  }
}
