#include "SmartHangarTask.h"
#include <Arduino.h>

SmartHangarTask::SmartHangarTask(Led *l1, Led *l2, Led *l3, Button *btn,
                                 Sonar *s, Pir *p, ServoMotor *sm,
                                 TempSensor *t, LcdDisplay *l) {
  this->l1 = l1;
  this->l2 = l2;
  this->l3 = l3;
  this->resetBtn = btn;
  this->sonar = s;
  this->pir = p;
  this->servo = sm;
  this->temp = t;
  this->lcd = l;
}

void SmartHangarTask::init(int period) {
  Task::init(period);
  state = REST;
  preAlarm = false;
  l1->switchOn();
  l2->switchOff();
  l3->switchOff();
  servo->off(); // Closed
  lcd->print("DRONE INSIDE");
  Serial.println("DRONE INSIDE");
}

void SmartHangarTask::setAlarm() {
  if (state != ALARM) {
    state = ALARM;
    l1->switchOff();
    l2->switchOff();
    l3->switchOn();
    servo->off(); // Close door
    lcd->print("ALARM");
    Serial.println("ALARM");
  }
}

bool SmartHangarTask::isAlarm() { return state == ALARM; }

void SmartHangarTask::tick() {
  switch (state) {
  case REST:
    // Wait for TO command
    if (Serial.available() > 0) {
      String cmd = Serial.readStringUntil('\n');
      if (cmd == "TO" && !preAlarm) {
        state = TAKE_OFF;
        l1->switchOff();
        servo->setPosition(90); // Open
        lcd->print("TAKE OFF");
        Serial.println("TAKE OFF");
        stateStartTime = millis();
      }
    }
    break;

  case TAKE_OFF:
    // Wait for drone to exit (Sonar > D1 for T1)
    if (sonar->getDistance() > D1) {
      if (millis() - stateStartTime > T1) {
        state = TO_OUT;
        servo->setPosition(0); // Close
        lcd->print("DRONE OUT");
        Serial.println("DRONE OUT");
      }
    } else {
      stateStartTime = millis(); // Reset timer if distance is small
    }
    break;

  case TO_OUT:
    // Wait for LD command
    if (Serial.available() > 0) {
      String cmd = Serial.readStringUntil('\n');
      if (cmd == "LD" && !preAlarm) {
        // Check PIR
        if (pir->isDetected()) {
          state = LANDING;
          servo->setPosition(90); // Open
          lcd->print("LANDING");
          Serial.println("LANDING");
          stateStartTime = millis();
        }
      }
    }
    break;

  case LANDING:
    // Wait for drone to enter (Sonar < D2 for T2)
    if (sonar->getDistance() < D2) {
      if (millis() - stateStartTime > T2) {
        state = REST;
        servo->setPosition(0); // Close
        l1->switchOn();
        lcd->print("DRONE INSIDE");
        Serial.println("DRONE INSIDE");
      }
    } else {
      stateStartTime = millis();
    }
    break;

  case ALARM:
    if (resetBtn->isPressed()) {
      state = REST;
      l3->switchOff();
      l1->switchOn();
      lcd->print("DRONE INSIDE");
      Serial.println("REST");
    }
    break;
  }
}
