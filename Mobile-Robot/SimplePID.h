#ifndef SimplePID_H
#define SimplePID_H

#include <Arduino.h>
#include <Wire.h>
#include <math.h>

class SimplePID {
private:
  float kp, kd, ki, umax;
  float eprev, eintegral;
  float filter_coeff;  // For derivative filtering

public:
  // Default initialization list
  SimplePID()
    : kp(1), kd(0), ki(0), umax(255), eprev(0.0), eintegral(0.0), filter_coeff(0.1) {}

  // Set the parameters
  void setParams(float kpIn, float kdIn, float kiIn, float umaxIn, float filter_coeffIn) {
    kp = kpIn;
    kd = kdIn;
    ki = kiIn;
    umax = umaxIn;
    filter_coeff = filter_coeffIn;
  }

  void evalu(int value, int target, float deltaT, int &pwr) {
    // คำนวณ error
    float error = target - value;

    // Integral term with anti-windup
    if (abs(error) <= 10 || abs(umax - kp * error - kd * (error - eprev) / deltaT) < ki * error * deltaT) {
      eintegral += error * deltaT;
      eintegral = constrain(eintegral, -umax / ki, umax / ki);
    }

    // // Filtered derivative
    float raw_dedt = (error - eprev) / deltaT;
    float dedt = filter_coeff * raw_dedt + (1 - filter_coeff) * (kd * (error - eprev) / deltaT);

    // // Control signal
    float u = kp * error + kd * dedt + ki * eintegral;

    pwr = (int)u;
    eprev = error;  
    // Serial.print(" | u: ");
    // Serial.print(u);

  }
};

#endif