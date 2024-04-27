#include <WiiChuck.h>

enum DIRECTION {
  LEFT,
  RIGHT,
  UP,
  DOWN,
  CENTER
};

enum BUTTON {
  C,
  Z,
  NONE
};

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