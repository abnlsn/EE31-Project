/*
* Authors: Abe Nelson, Eric M. Rohloff
* Date: 12/5/2024
* 
*  Variable Definitions for Motor Control, calibrates motor to ensure the bot
*  travels in a straight line.
*/

#define BATTERY_LEVEL_OFFSET 60
#define RIGHT_DUTY_OFFSET -100
#define LEFT_DUTY_OFFSET -110
#define THRESHOLD 10
#define DEGREES_90 225
#define DEGREES_180 450

#define ROTATION_AMOUNT(deg) (deg * 2 + deg / 2)

#define LINEFOLLOW_OFFSET 20