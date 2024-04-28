#include <WiiChuck.h>
#include "Enums.h"

class Joystick {

private:
  Accessory nunchuck;

public:
  BUTTON getJoystickButtons();
  DIRECTION getJoystickDirection();
  void configure();
  void printJoystickButtons(BUTTON button);
  void printJoystickDirection(DIRECTION direction);
};