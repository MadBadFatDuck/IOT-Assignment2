#include "BlinkTask.h"
#include "Scheduler.h"
#include "SmartHangarTask.h"
#include "TempMonitorTask.h"
#include <Arduino.h>

// Pin Definitions
#define PIN_BUTTON 12
#define PIN_L1 2
#define PIN_L2 3
#define PIN_L3 4
#define PIN_SERVO 5
#define PIN_TRIG 9
#define PIN_ECHO 10
#define PIN_PIR 11
#define PIN_TEMP A0

Scheduler sched;

void setup() {
  Serial.begin(9600);

  Led *l1 = new Led(PIN_L1);
  Led *l2 = new Led(PIN_L2);
  Led *l3 = new Led(PIN_L3);
  Button *btn = new Button(PIN_BUTTON);
  Sonar *sonar = new Sonar(PIN_TRIG, PIN_ECHO);
  Pir *pir = new Pir(PIN_PIR);
  ServoMotor *servo = new ServoMotor(PIN_SERVO);
  TempSensor *temp = new TempSensor(PIN_TEMP);
  LcdDisplay *lcd = new LcdDisplay();

  lcd->init();

  SmartHangarTask *hangarTask =
      new SmartHangarTask(l1, l2, l3, btn, sonar, pir, servo,temp , lcd);
  BlinkTask *blinkTask = new BlinkTask(l2, hangarTask);
  TempMonitorTask *tempTask = new TempMonitorTask(temp, hangarTask);

  hangarTask->init(100); // 10Hz
  blinkTask->init(500);  // 2Hz (0.5s period)
  tempTask->init(500);   // 2Hz

  sched.init(50); // Base period 50ms
  sched.addTask(hangarTask);
  sched.addTask(blinkTask);
  sched.addTask(tempTask);
}

void loop() { sched.schedule(); }
