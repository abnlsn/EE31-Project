/*
* Authors: Abe Nelson, Eric M. Rohloff
* Date: 12/3/2024
* 
* Function Declarations for Sensing Module, used for sensing colors, and IR to 
* follow lanes and detect walls
*/
#ifndef SENSING_H
#define SENSING_H

int sensing_IR_th_calculated;

// Color for Line Sensing
typedef enum {
    COLOR_RED,
    COLOR_YELLOW,
    COLOR_BLUE,
    COLOR_BLACK,
    COLOR_UNSURE
} SensorColor;


// Print out color Values for Debugging
#define DEBUG_PRINT_COLOR(color_enum) {\
    if (color_enum == COLOR_RED) {\
      Serial.print("RED");\
    } else if (color_enum == COLOR_YELLOW) {\
      Serial.print("YELLOW");\
    } else if (color_enum == COLOR_BLUE) {\
      Serial.print("BLUE");\
    } else if (color_enum == COLOR_BLACK) {\
      Serial.print("BLACK");\
    } else {\
      Serial.print("UNSURE");\
    }\
}

// Set up the sensing and the IR functionality
void sensing_setup();
int sensing_readIRValue();

// Function for getting colors from the sensors
SensorColor sensing_readLeftColor();
SensorColor sensing_readRightColor();

SensorColor sensing_readRightAverage();
SensorColor sensing_readLeftAverage();

// Sensing Functions for getting and starting the sensing logic
void sensing_loop();
bool sensing_colorReady();
void sensing_startColors(); 

void sensing_calculate_IR();

#endif