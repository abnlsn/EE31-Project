/*
* Authors: Abe Nelson, Eric M. Rohloff
* Date: 12/3/2024
* 
* Function Declarations for Sensing Module, used for sensing colors, and IR to 
* follow lanes and detect walls
*/
#ifndef SENSING_H
#define SENSING_H

// Color for Line Sensing
typedef struct {
    int red;
    int green;
    int blue;
} Color;

// Set up the sensing and the IR functionality
void sensing_setup();
int sensing_readIRValue();

// Function for getting colors from the sensors
Color sensing_readLeftColor();
Color sensing_readRightColor();

// Sensing Functions for getting and starting the sensing logic
void sensing_loop();
bool sensing_colorReady();
void sensing_readColors(); 

#endif