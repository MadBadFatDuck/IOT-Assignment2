#ifndef __TEMPSENSOR__
#define __TEMPSENSOR__

#include <Arduino.h>
/*ATTACH TMP36 to 3.3V */
class TempSensor {
  int pin;

public:
  TempSensor(int pin) { this->pin = pin; }

  float getTemperature() {
    int value = analogRead(pin);
    float voltage = value * (5 / 1024.0);
    float temperature = (voltage - 0.5) * 100; // TMP36
    return temperature;
  }
};

#endif
