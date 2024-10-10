#include "Led.h"

Led led1(LED_BUILTIN);

void setup() {

}

void loop() {
  led1.on();
  delay(1000);
  led1.off();
  delay(1000);
}