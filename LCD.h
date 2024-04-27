#include <LiquidCrystal.h>
#include "Arduino.h"

class LCD : public LiquidCrystal {
public:
  LCD(uint8_t rs, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3)
    : LiquidCrystal(rs, enable, d0, d1, d2, d3){};
  
  void configure();
  void shiftDown();
  void shiftLeft();
  void shiftRight();

private:
};