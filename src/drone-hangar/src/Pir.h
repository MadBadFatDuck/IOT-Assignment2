#ifndef __PIR__
#define __PIR__

#include <Arduino.h>

class Pir {
  int pin;

public:
  Pir(int pin) {
    this->pin = pin;
    pinMode(pin, INPUT);
  }
  bool isDetected() { return digitalRead(pin) == HIGH; }
};

#endif
