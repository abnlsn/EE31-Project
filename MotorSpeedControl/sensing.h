#ifndef SENSING_H
#define SENSING_H

typedef struct {
    int red;
    int green;
    int blue;
} Color;

void sensing_setup();
int sensing_readIRValue();
Color sensing_readLeftColor();
Color sensing_readRightColor();

void sensing_loop();
bool sensing_colorReady();


void sensing_readColors(); 

#endif