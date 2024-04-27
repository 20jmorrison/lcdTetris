#include "LCD.h"
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

void LCD::configure() {
  begin(16, 2);
  createChar(0, L);
  clear();
  write((uint8_t)0);
  Serial.println("LCD CONFIGURED");
}