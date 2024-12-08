/*
* Authors: Abe Nelson, Eric M. Rohloff
* Date: 12/5/2024
* 
* Function declarations for motor control and calibration, functions include
* setting the motor speed, direction, and the amount of degrees to rotate in
* order for the bot to move.
*/
#ifndef MOTOR_SPEED_H

#include "state_machine.h"
#include "motor_calibration.h"

// Functions to run the motor
void motorspeed_setup();
void motorspeed_loop();

// Directional and rotational functions for the motor
void motorspeed_set_direction(int new_direction);
void motorspeed_set_offset(int new_offset);
void motorspeed_rotate(int amount);
bool motorspeed_isrotating();

// Functions to control the wheels 
void left_fwd(int duty);
void right_fwd(int duty);
void left_rev(int duty);
void right_rev(int duty);

#endif