#ifndef __LCDDISPLAY__
#define __LCDDISPLAY__

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

class LcdDisplay {
  LiquidCrystal_I2C lcd;

public:
  LcdDisplay()
      : lcd(0x27, 20,
            4) { // Address 0x27, 20 chars, 4 lines (or 16x2 depending on model)
  }

  void init() {
    lcd.init();
    lcd.backlight();
  }

  void print(const char *msg) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(msg);
  }

  void printLine(int line, const char *msg) {
    lcd.setCursor(0, line);
    lcd.print(msg);
  }
};

#endif
