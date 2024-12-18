#include "motor_speed.h"
#include "sensing.h"
#include "state_machine.h"
#include "wifi_client.h"

void setup() {
  Serial.begin(9600);
  motorspeed_setup();
  sensing_setup();
  statemachine_setup();

  delay(100);
}


void loop() {
  Serial.println("");
  motorspeed_loop();
  sensing_loop();
  statemachine_run();

  delay(50);
}