#include "motor_speed.h"

const int IR_read = A0;

void setup() {
  Serial.begin(9600);
  motorspeed_setup();
}

void loop() {
  motorspeed_loop();
  Serial.println(analogRead(IR_read));

  String msg = Serial.readString();
  msg.trim();
  Serial.println(msg);

  statemachine_update(msg);
}