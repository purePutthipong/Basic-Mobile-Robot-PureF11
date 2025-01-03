#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor {
private:
  byte IN1;
  byte IN2;
  byte EN;

  void init();

public:
  Motor(byte IN1, byte IN2, byte EN);
  void move(int Speed);
  void off();
};

#endif
