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

#define LEFT_BTN 8
#define RIGHT_BTN 7
#define DOWN_BTN 17
#define ROTATE_BTN 16

#include "LCD.h"
#include "protothreads.h"


LCD lcd(RS, EN, D4, D5, D6, D7);
pt ptMove;

int moveThread(struct pt* pt) {
  PT_BEGIN(pt);

  for (;;) {
    lcd.shiftDown();
    PT_SLEEP(pt, 500);
  }
  PT_END(pt);
}


void setup() {
  Serial.begin(BAUD);
  
  pinMode(LEFT_BTN, INPUT_PULLUP);
  pinMode(RIGHT_BTN, INPUT_PULLUP);
  pinMode(DOWN_BTN, INPUT_PULLUP);
  pinMode(ROTATE_BTN, INPUT_PULLUP);

  lcd.configure();

  PT_INIT(&ptMove);
}

void loop() {
  PT_SCHEDULE(moveThread(&ptMove));
  int leftVal = digitalRead(LEFT_BTN);
  int rightVal = digitalRead(RIGHT_BTN);

  if(rightVal == 0){
    lcd.shiftRight();
    delay(100);
  }
  else if(leftVal == 0){
    lcd.shiftLeft();
    delay(100);
  }


}
