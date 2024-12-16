/*
* Authors: Abe Nelson, Eric M. Rohloff
* Date: 12/5/2024
* 
*  Variable Definitions for Motor Control, calibrates motor to ensure the bot
*  travels in a straight line.
*/
#define BATTERY_LEVEL_OFFSET 40
#define RIGHT_DUTY_OFFSET -100 - BATTERY_LEVEL_OFFSET
#define LEFT_DUTY_OFFSET -100 - BATTERY_LEVEL_OFFSET
#define THRESHOLD 10
#define DEGREES_90 200
#define DEGREES_180 188

#define LINEFOLLOW_OFFSET 25