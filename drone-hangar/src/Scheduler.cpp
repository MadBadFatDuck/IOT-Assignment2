#include "Scheduler.h"
#include <Arduino.h>

void Scheduler::init(int basePeriod) {
  this->basePeriod = basePeriod;
  nTasks = 0;
}

bool Scheduler::addTask(Task *task) {
  if (nTasks < MAX_TASKS) {
    taskList[nTasks] = task;
    nTasks++;
    return true;
  } else {
    return false;
  }
}

void Scheduler::schedule() {
  unsigned long startTime = millis();

  for (int i = 0; i < nTasks; i++) {
    if (taskList[i]->isActive() &&
        taskList[i]->updateAndCheckTime(basePeriod)) {
      taskList[i]->tick();
    }
  }

  unsigned long endTime = millis();
  unsigned long elapsed = endTime - startTime;

  if (elapsed < basePeriod) {
    delay(basePeriod - elapsed);
  }
}
