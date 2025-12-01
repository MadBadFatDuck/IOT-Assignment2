#ifndef __SERVOMOTOR__
#define __SERVOMOTOR__

#include <Arduino.h>
#include <Servo.h>

class ServoMotor {
  int pin;
  Servo servo;

public:
  ServoMotor(int pin) { this->pin = pin; }

  void on() { servo.attach(pin); }

  void setPosition(int angle) { servo.write(angle); }

  void off() { servo.detach(); }
};

#endif
