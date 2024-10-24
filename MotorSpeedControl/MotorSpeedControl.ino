#include "motor_speed.h"

void setup() {
  Serial.begin(9600);
  motorspeed_setup();
}

void loop() {
  motorspeed_loop();
}