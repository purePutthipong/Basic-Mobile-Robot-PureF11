#include "Motor.h"



Motor::Motor(byte IN1, byte IN2, byte EN) {
  this->IN1 = IN1;
  this->IN2 = IN2;
  this->EN = EN;

  init();
}

void Motor::init() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN, OUTPUT);

  off();
}

void Motor::move(int Speed) {

  bool dir = (Speed >= 0 ? true : false);
  Speed = abs(Speed);

  digitalWrite(IN1, dir);
  digitalWrite(IN2, !dir);
  analogWrite(EN, Speed);

}

void Motor::off() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(EN, 0);
}
