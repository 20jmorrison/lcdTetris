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
#include "Enums.h"
#include "protothreads.h"



LCD lcd(RS, EN, D4, D5, D6, D7);
Joystick joystick;
DIRECTION currDirection;
BUTTON currButton;
pt ptMove;
pt ptJoystick;

int moveThread(struct pt* pt) {
  PT_BEGIN(pt);

  for (;;) {
    lcd.shiftDown();
    PT_SLEEP(pt, 1000);
  }
  PT_END(pt);
}

int joystickThread(struct pt* pt) {
  PT_BEGIN(pt);

  for (;;) {
    currDirection = joystick.getJoystickDirection();
    currButton = joystick.getJoystickButtons();
    switch (currButton) {
      case C:
        {
          lcd.shiftRight();
          break;
        }
      case Z:
        {
          lcd.shiftLeft();
          break;
        }
      default:
        {
          break;
        }
    }
    lcd.rotatePiece(currDirection);
    PT_SLEEP(pt, 50);
  }
  PT_END(pt);
}

void setup() {
  Serial.begin(BAUD);

  lcd.configure();
  joystick.configure();

  PT_INIT(&ptMove);
}

void loop() {
  PT_SCHEDULE(moveThread(&ptMove));
  PT_SCHEDULE(joystickThread(&ptJoystick));
}
