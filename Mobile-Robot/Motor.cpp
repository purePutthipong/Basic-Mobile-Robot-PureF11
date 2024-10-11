#include "Motor.h"



Motor::Motor(byte IN1 , byte IN2 , byte EN ) {
  this->IN1 = IN1;
  this->IN2 = IN2;
  this->EN  = EN ;

  init();
}

void Motor::init() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN , OUTPUT);
  
  off();
}

void Motor::move(int Speed) {
    if (Speed > 0) {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(EN, constrain(Speed, 0, 255));
  } else if (Speed < 0) {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      analogWrite(EN, -(constrain(Speed, 0, 255)));
  } else {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      analogWrite(EN, 0);
  }
}

void Motor::off() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(EN, 0);
}