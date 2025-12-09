#ifndef __BUTTON__
#define __BUTTON__

#include <Arduino.h>

class Button {
  int pin;

public:
  Button(int pin) {
    this->pin = pin;
    pinMode(pin, INPUT);
  }
  bool isPressed() { return digitalRead(pin) == 1; }
  int getPin() { return pin; }
};

#endif
