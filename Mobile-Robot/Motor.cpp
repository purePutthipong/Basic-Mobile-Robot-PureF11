#include "Motor.h"

Motor::Motor(byte IN1, byte IN2, byte EN)
  : IN1(IN1), IN2(IN2), EN(EN) {
  init();
}

void Motor::init() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN, OUTPUT);
  off();
}

void Motor::move(int Speed) {
  // Serial.print(" | Speed: ");
  // Serial.print(Speed);

  bool dir = Speed >= 0;

  Speed = abs(Speed);
  Speed = constrain(Speed, 0, 255);  // Ensure Speed is within PWM range

  if (Speed == 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  } else {
    digitalWrite(IN1, dir);
    digitalWrite(IN2, !dir);
  }
  analogWrite(EN, Speed);
}

void Motor::off() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(EN, 0);
}


