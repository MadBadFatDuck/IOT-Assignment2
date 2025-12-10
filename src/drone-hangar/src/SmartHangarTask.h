#ifndef __SMARTHANGARTASK__
#define __SMARTHANGARTASK__

#include "Button.h"
#include "LcdDisplay.h"
#include "Led.h"
#include "Pir.h"
#include "ServoMotor.h"
#include "Sonar.h"
#include "Task.h"
#include "TempSensor.h"

enum State { REST, TAKE_OFF, TO_OUT, LANDING, HANGAR_ALARM };

class SmartHangarTask : public Task {
  State state;
  bool preAlarm;
  Led *l1;
  Led *l2;
  Led *l3;
  Button *resetBtn;
  Sonar *sonar;
  Pir *pir;
  ServoMotor *servo;
  TempSensor *temp;
  LcdDisplay *lcd;

  // Parameters
  float D1 = 50;          // meters
  float D2 = 30;          // meters
  unsigned long T1 = 2000; // ms
  unsigned long T2 = 2000; // ms

  unsigned long stateStartTime;

public:
  SmartHangarTask(Led *l1, Led *l2, Led *l3, Button *btn, Sonar *s, Pir *p,
                  ServoMotor *sm, TempSensor *t, LcdDisplay *l);
  void init(int period);
  void tick();
  void setAlarm();
  bool isAlarm();
  bool isBlinkingPhase() { return state == TAKE_OFF || state == LANDING; }
  void setPreAlarm(bool active);
};

#endif
