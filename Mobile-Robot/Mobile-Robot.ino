#include "Led.h"
#include "Motor.h"

Led led1(LED_BUILTIN);
Motor Motor1(8 , 9 , 10);

void setup() {

}

void loop() {

  led1.on();
  delay(1000);
  led1.off();
  delay(1000);
  
}