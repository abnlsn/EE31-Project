#include "motor_speed.h"
#include "sensing.h"

void setup() {
  Serial.begin(9600);
  motorspeed_setup();
  sensing_setup();
}

void loop() {
  // motorspeed_loop();

  Serial.println(sensing_readIRValue());

  String msg = Serial.readString();
  msg.trim();
  Serial.println(msg);

  statemachine_update(msg);

  statemachine_run();

  delay(100);
}