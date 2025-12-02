#ifndef __SONAR__
#define __SONAR__

#include <Arduino.h>

class Sonar {
  int trigPin;
  int echoPin;

public:
  Sonar(int trigPin, int echoPin) {
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
  }

  float getDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH);
    float distance = duration * 0.034 / 2;
    return distance;
  }
};

#endif
