/*
* Authors: Abe Nelson, Eric M. Rohloff
* Date: 12/5/2024
* 
*  Variable Definitions for Motor Control, calibrates motor to ensure the bot
*  travels in a straight line.
*/
#define BATTERY_LEVEL_OFFSET 20
#define RIGHT_DUTY_OFFSET -90 - BATTERY_LEVEL_OFFSET
#define LEFT_DUTY_OFFSET -120 - BATTERY_LEVEL_OFFSET
#define THRESHOLD 10


#define RIGHT_DEGREES_90 300
#define RIGHT_DEGREES_180 580
#define LEFT_DEGREES_90 -300
#define LEFT_DEGREES_180 -600

#define LINEFOLLOW_OFFSET 25