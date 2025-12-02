#ifndef __TEMPSENSOR__
#define __TEMPSENSOR__

#include <Arduino.h>

class TempSensor {
  int pin;

public:
  TempSensor(int pin) { this->pin = pin; }

  float getTemperature() {
    int value = analogRead(pin);
    float voltage = value * (5.0 / 1023.0);
    float temperature = (voltage - 0.5) * 100; // TMP36
    return temperature;
  }
};

#endif
