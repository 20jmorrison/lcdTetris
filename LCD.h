#include <LiquidCrystal.h>
#include "Arduino.h"
#include "Enums.h"
class LCD : public LiquidCrystal {
public:
  LCD(uint8_t rs, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3)
    : LiquidCrystal(rs, enable, d0, d1, d2, d3){};
  
  void configure();
  void shiftDown();
  void shiftLeft();
  void shiftRight();
  void rotatePiece(DIRECTION direction);


private:
  int cursorX = 14;
  int cursorY = 0;
  void swapRectangles(uint8_t _rectA[], uint8_t _rectB[]);
  void setPiece(uint8_t _piece[]);
  int downShifts = 0;
  int rightShifts = 0;
  void moveToPosition();
  void drawBottom();
  void drawRectangles();
};



