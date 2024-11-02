#include "Led.h"
#include "Motor.h"
#include "pio_encoder.h"
#include "SimplePID.h"

#define NMOTORS 4

SimplePID pid[NMOTORS];
Led led1(LED_BUILTIN);

// Globals
long prevT = micros();
volatile int posi[] = { 0, 0, 0, 0 };

Motor M[NMOTORS] = {
  Motor(0, 1, 20),
  Motor(6, 7, 21),
  Motor(12, 13, 27),
  Motor(16, 17, 26)
};

PioEncoder encoder[NMOTORS] = {
  PioEncoder(2),
  PioEncoder(4),
  PioEncoder(14),
  PioEncoder(18)
};

void moveMecanumWithPID(int x, int y, int rotation) {
  int motorTarget[4];
  bool reachedTarget = false;

  while (!reachedTarget) {
    reachedTarget = true;

    // คำนวณเป้าหมายสำหรับแต่ละมอเตอร์จากการเคลื่อนที่ในแกน X, Y และการหมุน
    motorTarget[0] = y + x + rotation;  // Front-left motor
    motorTarget[1] = y - x - rotation;  // Front-right motor
    motorTarget[2] = y - x + rotation;  // Back-left motor
    motorTarget[3] = y + x - rotation;  // Back-right motor

    // คำนวณความเร็วโดยใช้ PID
    int motorPower[4];
    long currT = micros();
    float deltaT = ((float)(currT - prevT)) / (1.0e6);
    prevT = currT;

    int pos[NMOTORS];
    noInterrupts();
    for (int k = 0; k < NMOTORS; k++) {
      pos[k] = (k == 0 || k == 2) ? -encoder[k].getCount() : encoder[k].getCount();
    }
    interrupts();

    for (int i = 0; i < NMOTORS; i++) {
      pid[i].evalu(pos[i], motorTarget[i], deltaT, motorPower[i]);
      M[i].move(motorPower[i]);

      Serial.print(" | Motor ");
      Serial.print(i);
      Serial.print(" | pos: ");
      Serial.print(pos[i]);
      Serial.print(" | Target: ");
      Serial.print(motorTarget[i]);

      if (abs(motorTarget[i] - pos[i]) > 100) {  // กำหนด tolerance
        reachedTarget = false;
      }
    }
    Serial.println("");
  }

  // หยุดมอเตอร์ทั้งหมดเมื่อถึงเป้าหมาย
  for (int k = 0; k < NMOTORS; k++) {
    M[k].move(0);
  }
}

void setup() {
  Serial.begin(115200);

  for (int k = 0; k < NMOTORS; k++) {
    encoder[k].begin();                           // เริ่มการทำงานของ encoder
    pid[k].setParams(0.5, 0.12, 0.01, 255, 0.2);  // ตั้งค่าพารามิเตอร์ PID
  }

  Serial.println("Enter values for X, Y, and Rotation:");
}

int count = 0;
int point[2] = { 0, 0 };
void loop() {
  if (Serial.available() > 0) {
    int x = Serial.parseInt();         // รับค่าการเคลื่อนที่ในแกน X
    int y = Serial.parseInt();         // รับค่าการเคลื่อนที่ในแกน Y
    // int rotation = Serial.parseInt();  // รับค่าการหมุน

    Serial.print(" | point[0]: ");
    Serial.print(point[0]);
    Serial.print(" | point[1]: ");
    Serial.print(point[1]);

    if (count < 1) {
      count += 1;

      // เรียกฟังก์ชันเพื่อเคลื่อนที่ตามทิศทางที่กำหนดโดยใช้ PID ในการควบคุมความเร็ว
      Serial.print("Moving with X: ");
      Serial.print(x);
      Serial.print(", Y: ");
      Serial.print(y);
      // Serial.print(", Rotation: ");
      // Serial.println(rotation);

      moveMecanumWithPID(y*10000, x*10000, 0);

      point[0] = x;
      point[1] = y;
    } else {s0 
      count = 0;
    }
  }
}
