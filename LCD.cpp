#include "LCD.h"
uint8_t topLeft[8] = {
  0b00010,
  0b00010,
  0b00011,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
};
uint8_t topRight[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
};
uint8_t bottomLeft[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
};
uint8_t bottomRight[8] = {
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
  createChar(0, topLeft);
  clear();
  setCursor(14, 0);
  write((uint8_t)0);
  Serial.println("LCD CONFIGURED");
}

void LCD::displayQuadrants(){
  
}

void LCD::shiftDown(){
  for (int i = 0; i < 8; i++) {
    topLeft[i] = (topLeft[i] << 1) | (topLeft[i] >> 4);
  }
  createChar(0, topLeft);
  clear();
  setCursor(14, 0);
  write((uint8_t)0);
}

void LCD::shiftLeft(){
  uint8_t wrapVal = topLeft[0];
  for (int i = 0; i < 7; i++) {
    topLeft[i] = topLeft[i + 1];
  }
  topLeft[7] = wrapVal;
  createChar(0, topLeft);
  clear();
  setCursor(14, 0);
  write((uint8_t)0);
}

void LCD::shiftRight(){
  uint8_t wrapVal = topLeft[7];
  for (int i = 7; i > 0; i--) {
    topLeft[i] = topLeft[i - 1];
  }
  topLeft[0] = wrapVal;
  createChar(0, topLeft);
  clear();
  setCursor(14, 0);
  write((uint8_t)0);
}