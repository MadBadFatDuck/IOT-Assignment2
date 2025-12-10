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
  servo->on(); // Closed
  servo->setPosition(0);
  lcd->print("DRONE INSIDE");
  Serial.println("DRONE INSIDE");
}

void SmartHangarTask::setAlarm() {
  if (state != HANGAR_ALARM) {
    state = HANGAR_ALARM;
    l1->switchOff();
    l2->switchOff();
    l3->switchOn();
    servo->setPosition(0); // Close door
    lcd->print("ALARM");
    Serial.println("ALARM");
  }
}

bool SmartHangarTask::isAlarm() { return state == HANGAR_ALARM; }

void SmartHangarTask::tick() {

  if (state == REST) {
    // REST Case
    if (Serial.available() > 0) {
      String cmd = Serial.readStringUntil('\n');
      cmd.trim();
      if (cmd == "TO" && !preAlarm) {
        state = TAKE_OFF;
        servo->setPosition(90);
        lcd->print("TAKE OFF");
        Serial.println("TAKE OFF");
        stateStartTime = millis();
      }
    }
  } else if (state == TAKE_OFF) {
    if (sonar->getDistance() > D1) {
      if (millis() - stateStartTime > T1) {
        state = TO_OUT;
        servo->setPosition(0);
        lcd->print("DRONE OUT");
        Serial.println("DRONE OUT");
      }
    } else {
      stateStartTime = millis();
    }
  } else if (state == TO_OUT) {
    if (Serial.available() > 0) {
      String cmd = Serial.readStringUntil('\n');
      cmd.trim();
      if (cmd == "LD" && !preAlarm) {
        if (pir->isDetected()) {
          state = LANDING;
          servo->setPosition(90);
          lcd->print("LANDING");
          Serial.println("LANDING");
          stateStartTime = millis();
        }
      }
    }
  } else if (state == LANDING) {
    float distance = sonar->getDistance();
    Serial.print("Distance:"); Serial.println(distance);
    if (sonar->getDistance() < D2) {
      if (millis() - stateStartTime > T2) {
        state = REST;
        servo->setPosition(0);
        lcd->print("DRONE INSIDE");
        Serial.println("DRONE INSIDE");
      }
    } else {
      stateStartTime = millis();
    }
  } else if (state == HANGAR_ALARM) {
    if (resetBtn->isPressed()) {
      state = REST;
      l3->switchOff();
      l1->switchOn();
      lcd->print("DRONE INSIDE");
      Serial.println("REST");
    }
  }
}

void SmartHangarTask::setPreAlarm(bool active) {
  if (active && !preAlarm) {
    Serial.println("PRE-ALARM");
  }
  preAlarm = active;
}
