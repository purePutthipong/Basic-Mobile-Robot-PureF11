#ifndef LED_H
#define LED_H

#include <Arduino.h>

class Led {
private:
  byte pin;
  void init();

public:
  Led(byte pin);
  void on();
  void off();
};

#endif
