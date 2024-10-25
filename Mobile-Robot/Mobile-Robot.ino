#include "Led.h"
#include "Motor.h"
#include "pio_encoder.h"
#include "SimplePID.h"

#define NMOTORS 4

SimplePID pid[NMOTORS];
Led led1(LED_BUILTIN);

// Globals
long prevT = 0;
volatile int posi[] = { 0, 0, 0, 0 };

Motor M[NMOTORS] = {
  Motor(0, 1, 20),
  Motor(4, 5, 21),
  Motor(12, 13, 22),
  Motor(16, 17, 26)
};

PioEncoder encoder[NMOTORS] = {
  PioEncoder(2),
  PioEncoder(6),
  PioEncoder(14),
  PioEncoder(18)
};


// Motor Motor1(0, 1, 20);
// // PioEncoder encoder1(2);

// Motor Motor2(4, 5, 21);
// PioEncoder encoder2(6);

// Motor Motor3(12, 13, 22);
// // PioEncoder encoder3(14);

// Motor Motor4(16, 17, 26);
// // PioEncoder encoder4(18);



void setup() {
  Serial.begin(115200);

  for (int k = 0; k < NMOTORS; k++) {
    encoder[k].begin();                // เริ่มการทำงานของ encoder
    pid[k].setParams(1.2, 0.1, 0, 255);  // ตั้งค่าพารามิเตอร์ PID
  }

  Serial.println("target pos");
}

void loop() {

  // M[0].move(80);
  // M[1].move(80);
  // M[2].move(80);
  // M[3].move(80);

  // Serial.print(encoder[0].getCount());
  // Serial.print("\t");
  // Serial.print(encoder[1].getCount());
  // Serial.print("\t");
  // Serial.print(encoder[2].getCount());
  // Serial.print("\t");
  // Serial.print(encoder[3].getCount());
  // Serial.println("\t");

  // set target position
  int target[NMOTORS];
  target[0] = -750 * sin(prevT / 1e6);
  target[1] = 750 * sin(prevT / 1e6);
  target[2] = -750 * sin(prevT / 1e6);
  target[3] = 750 * sin(prevT / 1e6);

  // time difference
  long currT = micros();
  float deltaT = ((float)(currT - prevT)) / (1.0e6);
  prevT = currT;

  // Read the position
  int pos[NMOTORS];
  noInterrupts();  // disable interrupts temporarily while reading
  for (int k = 0; k < NMOTORS; k++) {
    if (k == 0 || k == 2) {
      pos[k] = -encoder[k].getCount();
    }else{
      pos[k] = encoder[k].getCount();
    }
  }
  interrupts();  // turn interrupts back on

  // loop through the motors
  for (int k = 0; k < NMOTORS; k++) {
    int pwr, dir;
    // evaluate the control signal
    pid[k].evalu(pos[k], target[k], deltaT, pwr, dir);
    // signal the motor
    M[k].move(pwr);
  }

  for (int k = 0; k < NMOTORS; k++) {
    Serial.print(target[k]);
    Serial.print(" ");
    Serial.print(pos[k]);
    Serial.print(" ");
  }
  Serial.println();
}