#include "motor_speed.h"
#include "sensing.h"

#ifndef MOTOR_SPEED_H
#define MOTOR_SPEED_H


void setup() {
  Serial.begin(9600);
  motorspeed_setup();
  sensing_setup();

  delay(100);
  motorspeed_rotate(DEGREES_90);
  // motorspeed_set_direction(1);
}

void loop() {
  motorspeed_loop();

  // Serial.println(sensing_readIRValue());

  // String msg = Serial.readString();
  // msg.trim();
  // Serial.println(msg);

  // statemachine_update(msg);

  // statemachine_run();
}

#endif