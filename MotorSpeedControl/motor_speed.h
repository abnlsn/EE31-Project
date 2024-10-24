#include "EE31_motor_drive.h"
#include "motor_calibration.h"

void motorspeed_setup();
void motorspeed_loop();

void motorspeed_fwd();
void motorspeed_reverse();

void left_fwd(int duty);
void right_fwd(int duty);
void left_rev(int duty);
void right_rev(int duty);