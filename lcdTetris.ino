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

enum INPUT {
  RIGHT,
  LEFT,
  DOWN,
  ROTATE,
  NONE
}userInput;

LCD lcd(RS, EN, D4, D5, D6, D7);
pt ptMove;
pt ptInput;

int moveThread(struct pt* pt) {
  PT_BEGIN(pt);

  for (;;) {
    lcd.shiftDown();
    PT_SLEEP(pt, 500);
  }
  PT_END(pt);
}

int inputThread(struct pt* pt) {
  PT_BEGIN(pt);
  int right, left, down, rotate;
  for (;;) {
    right = !digitalRead(RIGHT_BTN); // These are input pullups, !'ing it is just to make the following code more readable 
    left = !digitalRead(LEFT_BTN);
    down = !digitalRead(DOWN_BTN);
    rotate = !digitalRead(ROTATE_BTN);

    if (right) { 
      userInput = RIGHT;
    }
    else if (left) {
      userInput = LEFT;
    }
    else if (down) {
      userInput = DOWN;
    }
    else if (rotate) {
      userInput = ROTATE;
    }
    else{
      // User isn't pressing a button
      userInput = NONE;
    }
    PT_SLEEP(pt, 100);
  }
  PT_END(pt);
}


void setup() {
  Serial.begin(BAUD);
  
  pinMode(LEFT_BTN, INPUT_PULLUP);
  pinMode(RIGHT_BTN, INPUT_PULLUP);
  pinMode(DOWN_BTN, INPUT_PULLUP);
  pinMode(ROTATE_BTN, INPUT_PULLUP);

  userInput = NONE;

  lcd.configure();

  PT_INIT(&ptMove);
  PT_INIT(&ptInput);
}


void loop() {
  PT_SCHEDULE(moveThread(&ptMove));
  PT_SCHEDULE(inputThread(&ptInput));

  printInput();

}


void printInput(){
  switch(userInput) {
    case 0:{
      Serial.println("RIGHT");
      break;
    }
    case 1:{
      Serial.println("LEFT");
      break;
    }
    case 2:{
      Serial.println("DOWN");
      break;
    }
    case 3:{
      Serial.println("ROTATE");
      break;
    }
    case 4:{
      Serial.println("NO INPUT");
      break;
    }
    default:{
      Serial.println("INPUT ERROR");
      break;
    }
  }
}




