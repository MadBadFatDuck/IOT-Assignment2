#ifndef __BLINKTASK__
#define __BLINKTASK__

#include "Led.h"
#include "SmartHangarTask.h"
#include "Task.h"

class BlinkTask : public Task {
  Led *led;
  SmartHangarTask *mainTask;
  bool ledState;

public:
  BlinkTask(Led *led, SmartHangarTask *mainTask) {
    this->led = led;
    this->mainTask = mainTask;
    ledState = false;
  }

  void init(int period) { Task::init(period); }

  void tick() {
    if (mainTask->isBlinkingPhase()) {
      if (ledState) {
        led->switchOff();
      } else {
        led->switchOn();
      }
      ledState = !ledState;
    } else {
      led->switchOff();
      ledState = false;
    }
  }
};

#endif
