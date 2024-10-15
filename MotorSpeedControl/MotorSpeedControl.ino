#include "EE31_motor_drive.h"

int left_motor_encoder = 3;

void setup() {
  statemachine_setup();
  Serial.begin(9600);
  pinMode(left_motor_encoder, INPUT);

  Serial.println("Duty Cycle,ms per rev");

  attachInterrupt(digitalPinToInterrupt(left_motor_encoder), rotation, RISING);
}



int last_millis = 0;

int count = 0;
int current_duty = 20;
float sum = 0;

const int NUM_ROTATIONS = 50;

void rotation() {
  int current = millis();
  int diff_time = current - last_millis;

  last_millis = current;

  if (last_millis == 0) return;

  float mps = 0.5 * 3.1415 / diff_time;
  // Serial.println(mps);

  sum += diff_time;

  count++;
  if (count > NUM_ROTATIONS) {
    count = 0;
    sum = sum / NUM_ROTATIONS;
    Serial.print(current_duty);
    Serial.print(",");
    Serial.print(sum);
    Serial.println(",");

    // reset
    sum = 0;
    current_duty += 5;
    left_fwd(current_duty);
  }
}

void loop() {
  if (current_duty > 255) {
    detachInterrupt(digitalPinToInterrupt(left_motor_encoder));
    Serial.println("Deactivated");
    left_fwd(0);
    while (true);
  }
  delay(100);
}

