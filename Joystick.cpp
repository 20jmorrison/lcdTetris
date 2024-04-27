#include "Joystick.h"

void Joystick::configure() {
  nunchuck.begin();
  nunchuck.type = NUNCHUCK;
  Serial.println("NUNCHUCK CONFIGURED");
}

BUTTON Joystick::getJoystickButtons() {
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

DIRECTION Joystick::getJoystickDirection() {
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

void Joystick::printJoystickButtons(BUTTON button) {
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

void Joystick::printJoystickDirection(DIRECTION direction) {
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
