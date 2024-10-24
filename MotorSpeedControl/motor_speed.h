#include "EE31_motor_drive.h"
#include "motor_calibration.h"

void motorspeed_setup();
void motorspeed_loop();

void motorspeed_set_direction(int new_direction);
void motorspeed_set_offset(int new_offset);

void left_fwd(int duty);
void right_fwd(int duty);
void left_rev(int duty);
void right_rev(int duty);