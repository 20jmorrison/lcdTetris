#include "LCD.h"
uint8_t rectA[8] = {
  0b00010,
  0b00010,
  0b00011,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
};
uint8_t rectB[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
};



void LCD::configure() {
  begin(16, 2);
  createChar(0, rectA);
  clear();
  setCursor(14, 0);
  write((uint8_t)0);
  Serial.println("LCD CONFIGURED");
}

void LCD::swapRectangles(uint8_t _rectA[], uint8_t _rectB[]){
  for (int i = 0; i < 8; i++){
    _rectA[i] = _rectB[i];
    _rectB[i] = 0b00000;
  }

}

void LCD::shiftDown() {
  bool rectAEmpty = true;
  for (int i = 0; i < 8; i++) {
    rectA[i] = (rectA[i] << 1) | (rectB[i] >> 5);
    rectB[i] = (rectB[i] << 1) | (rectA[i] >> 5);
    if (rectA[i] > 0){
      rectAEmpty = false;
    }
  }
  createChar(0, rectA);
  createChar(1, rectB);
  clear();
  setCursor(cursorX, cursorY);
  write((uint8_t)0);
  cursorX--;
  setCursor(cursorX, cursorY);
  write((uint8_t)1);
  cursorX++;
  if (rectAEmpty){ // as soon as the top rectangle is empty,
    swapRectangles(rectA, rectB);
    cursorX--;
    // swap rectA and rectB
    // decrement cursor x
  }
  delay(500);
}

void LCD::shiftLeft() {
  uint8_t wrapVal = rectA[0];
  for (int i = 0; i < 7; i++) {
    rectA[i] = rectA[i + 1];
  }
  rectA[7] = wrapVal;
  createChar(0, rectA);
  clear();
  setCursor(14, 0);
  write((uint8_t)0);
}

void LCD::shiftRight() {
  uint8_t wrapVal = rectA[7];
  for (int i = 7; i > 0; i--) {
    rectA[i] = rectA[i - 1];
  }
  rectA[0] = wrapVal;
  createChar(0, rectA);
  clear();
  setCursor(14, 0);
  write((uint8_t)0);
}