#ifndef __LED__
#define __LED__

#include "Light.h"
#include <Arduino.h>

class Led : public Light {
  int pin;

public:
  Led(int pin) {
    this->pin = pin;
    pinMode(pin, OUTPUT);
  }
  void switchOn() { digitalWrite(pin, HIGH); }
  void switchOff() { digitalWrite(pin, LOW); }
};

#endif
