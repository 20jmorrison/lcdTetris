#include "LCD.h"
#include "Sprites.h"
uint8_t rectA[8] = {
  0b00000,
  0b00000,
  0b00000,
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

uint8_t rectC[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
};

uint8_t rectD[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
};

//  A C
//  B D

void LCD::configure() {
  begin(16, 2);
  setPiece(L_0);
  createChar(0, rectA);
  clear();
  setCursor(14, 0);
  write((uint8_t)0);
  Serial.println("LCD CONFIGURED");
  drawBottom();
}

void LCD::drawBottom(){
  createChar(5, bottom_line);
  setCursor(0,0);
  write((uint8_t)5);
  setCursor(0,1);
  write((uint8_t)5);
  setCursor(cursorX, cursorY);
}

void LCD::drawRectangles(){
createChar(0, rectA);
  createChar(1, rectB);
  createChar(2, rectC);
  createChar(3, rectD);

  // Print rectA
  clear();
  setCursor(cursorX, cursorY);
  write((uint8_t)0);

  // Print rectB
  cursorX--;
  setCursor(cursorX, cursorY);
  write((uint8_t)1);
  cursorX++;

  // print rectC
  cursorY++;
  setCursor(cursorX, cursorY);
  write((uint8_t)2);
  cursorY--;

  // print rectD
  cursorX--;
  cursorY++;
  setCursor(cursorX, cursorY);
  write((uint8_t)3);
  cursorX++;
  cursorY--;
}


void LCD::swapRectangles(uint8_t _rectA[], uint8_t _rectB[]) {
  for (int i = 0; i < 8; i++) {
    _rectA[i] = _rectB[i];
    _rectB[i] = 0b00000;
  }
}

void LCD::setPiece(uint8_t _piece[]) {
  for (int i = 0; i < 8; i++) {
    rectA[i] = _piece[i];
    rectB[i] = 0b00000;
    rectC[i] = 0b00000;
    rectD[i] = 0b00000;
  }
}

void LCD::rotatePiece(DIRECTION direction) {
  switch (direction) {
    case DOWN:
      {
        setPiece(L_0);
        moveToPosition();
        break;
      }
    case UP:
      {
        setPiece(L_180);
        moveToPosition();
        break;
      }
    case LEFT:
      {
        setPiece(L_90);
        moveToPosition();
        break;
      }
    case RIGHT:
      {
        setPiece(L_270);
        moveToPosition();
        break;
      }
    default:
      {
        break;
      }
  }
}

void LCD::moveToPosition() {

  for (int i = 0; i < downShifts; i++) {
    bool rectAEmpty = true;
    bool rectCEmpty = true;
    for (int i = 0; i < 8; i++) {
      rectA[i] = (rectA[i] << 1) | (rectB[i] >> 5);
      rectB[i] = (rectB[i] << 1) | (rectA[i] >> 5);

      rectC[i] = (rectC[i] << 1) | (rectD[i] >> 5);
      rectD[i] = (rectD[i] << 1) | (rectC[i] >> 5);

      if (rectA[i] > 0) {
        rectAEmpty = false;
      }
      if (rectC[i] > 0) {
        rectCEmpty = false;
      }
    }

    if (rectAEmpty && rectCEmpty) {  // as soon as the top rectangle is empty,
      swapRectangles(rectA, rectB);
      swapRectangles(rectC, rectD);
      cursorX--;
      // swap rectA and rectB
      // decrement cursor x
    }
  }


  for (int i = 0; i < rightShifts; i++) {
    if (rectC[7] == 0) {             // if the last row of rectC is empty, we have space to shift right
      uint8_t wrapVal = rectA[7];    // save last row of A to append to C
      for (int i = 7; i > 0; i--) {  // shift A over
        rectA[i] = rectA[i - 1];
      }
      rectA[0] = 0b00000;            // set first row of a to 0
      for (int i = 7; i > 0; i--) {  // shift c over
        rectC[i] = rectC[i - 1];
      }
      rectC[0] = wrapVal;
    }

    if (rectD[7] == 0) {             // if the first row of rectA is empty, we have space to shift left
      uint8_t wrapVal = rectB[7];    // save first row of B to append to A
      for (int i = 7; i > 0; i--) {  // shift b over
        rectB[i] = rectB[i - 1];
      }
      rectB[0] = 0b00000;            // set last row of b to 0
      for (int i = 7; i > 0; i--) {  // shift a over
        rectD[i] = rectD[i - 1];
      }
      rectD[0] = wrapVal;
    }
  }
  drawRectangles();
  drawBottom();
}

void LCD::shiftDown() {

  for (int i = 0; i < 8; i++) {
    rectA[i] = (rectA[i] << 1) | (rectB[i] >> 5);
    rectB[i] = (rectB[i] << 1) | (rectA[i] >> 5);

    rectC[i] = (rectC[i] << 1) | (rectD[i] >> 5);
    rectD[i] = (rectD[i] << 1) | (rectC[i] >> 5);

  }

  drawRectangles();
  downShifts++;

  bool shouldSwitch = false;
  
  for(int i = 0; i < 8; i++){
    if(((rectB[i] >> 4) == 1) || ((rectD[i] >> 4) == 1)){
      shouldSwitch = true;
    }
  }
  Serial.println(shouldSwitch);
  if (shouldSwitch){
    swapRectangles(rectA, rectB);
    swapRectangles(rectC, rectD);
    cursorX--;
    downShifts = 0;
  }
  drawBottom();
}

void LCD::shiftLeft() {
  bool shiftedLeft = false;
  if (rectA[0] == 0) {             // if the first row of rectA is empty, we have space to shift left
    uint8_t wrapVal = rectC[0];    // save first row of B to append to A
    for (int i = 0; i < 7; i++) {  // shift b over
      rectC[i] = rectC[i + 1];
    }
    rectC[7] = 0b00000;            // set last row of b to 0
    for (int i = 0; i < 7; i++) {  // shift a over
      rectA[i] = rectA[i + 1];
    }
    rectA[7] = wrapVal;
    shiftedLeft = true;
  }
  if (rectB[0] == 0) {             // if the first row of rectA is empty, we have space to shift left
    uint8_t wrapVal = rectD[0];    // save first row of B to append to A
    for (int i = 0; i < 7; i++) {  // shift b over
      rectD[i] = rectD[i + 1];
    }
    rectD[7] = 0b00000;            // set last row of b to 0
    for (int i = 0; i < 7; i++) {  // shift a over
      rectB[i] = rectB[i + 1];
    }
    rectB[7] = wrapVal;
    shiftedLeft = true;
  }

  if (shiftedLeft) {
    rightShifts--;
  }

  drawRectangles();
  drawBottom();
}

void LCD::shiftRight() {
  bool shiftedRight = false;
  if (rectC[7] == 0) {             // if the last row of rectC is empty, we have space to shift right
    uint8_t wrapVal = rectA[7];    // save last row of A to append to C
    for (int i = 7; i > 0; i--) {  // shift A over
      rectA[i] = rectA[i - 1];
    }
    rectA[0] = 0b00000;            // set first row of a to 0
    for (int i = 7; i > 0; i--) {  // shift c over
      rectC[i] = rectC[i - 1];
    }
    rectC[0] = wrapVal;
    shiftedRight = true;
  }

  if (rectD[7] == 0) {             // if the first row of rectA is empty, we have space to shift left
    uint8_t wrapVal = rectB[7];    // save first row of B to append to A
    for (int i = 7; i > 0; i--) {  // shift b over
      rectB[i] = rectB[i - 1];
    }
    rectB[0] = 0b00000;            // set last row of b to 0
    for (int i = 7; i > 0; i--) {  // shift a over
      rectD[i] = rectD[i - 1];
    }
    rectD[0] = wrapVal;
    shiftedRight = true;
  }

  if (shiftedRight) {
    rightShifts++;
  }

  drawRectangles();
  drawBottom();
}



