#ifndef __TEMPMONITORTASK__
#define __TEMPMONITORTASK__

#include "SmartHangarTask.h"
#include "Task.h"
#include "TempSensor.h"

class TempMonitorTask : public Task {
  TempSensor *temp;
  SmartHangarTask *mainTask;

  float Temp1 = 25.0;      // Celsius
  float Temp2 = 30.0;      // Celsius
  unsigned long T3 = 3000; // ms
  unsigned long T4 = 3000; // ms

  unsigned long temp1StartTime;
  unsigned long temp2StartTime;
  bool temp1Active;
  bool temp2Active;

public:
  TempMonitorTask(TempSensor *t, SmartHangarTask *mt) {
    this->temp = t;
    this->mainTask = mt;
    temp1Active = false;
    temp2Active = false;
  }

  void init(int period) { Task::init(period); }

  void tick() {
    float currentTemp = temp->getTemperature();

    // Check Temp1
    if (currentTemp >= Temp1) {
      if (!temp1Active) {
        temp1StartTime = millis();
        temp1Active = true;
      } else {
        if (millis() - temp1StartTime > T3) {
          mainTask->setPreAlarm(true);
        }
      }
    } else {
      temp1Active = false;
      mainTask->setPreAlarm(false);
    }

    // Check Temp2
    if (currentTemp >= Temp2) {
      if (!temp2Active) {
        temp2StartTime = millis();
        temp2Active = true;
      } else {
        if (millis() - temp2StartTime > T4) {
          mainTask->setAlarm();
        }
      }
    } else {
      temp2Active = false;
    }
  }
};

#endif
