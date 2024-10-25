#ifndef SimplePID_H
#define SimplePID_H

#include <Arduino.h>
#include <Wire.h>
#include <math.h>

class SimplePID {
private:
  float kp, kd, ki, umax;
  float eprev, eintegral;

public:
  // Default initialization list
  SimplePID()
    : kp(1), kd(0), ki(0), umax(255), eprev(0.0), eintegral(0.0) {}

  // Set the parameters
  void setParams(float kpIn, float kdIn, float kiIn, float umaxIn) {
    kp = kpIn;
    kd = kdIn;
    ki = kiIn;
    umax = umaxIn;
  }

  // Evaluate the signal
  void evalu(int value, int target, float deltaT, int &pwr, int &dir) {
    // error
    int e = target - value;
    
    // derivative
    float dedt = (e - eprev) / (deltaT);

    // integral
    eintegral = eintegral + e * deltaT;

    // control signal
    float u = kp * e + kd * dedt + ki * eintegral;

    // motor power
    pwr = (int)fabs(u);
    if (pwr > umax) {
      pwr = umax;
    }

    // store previous error
    eprev = e;
  }
};

#endif