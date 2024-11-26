#include "sensing.h"

const int IR_read = A0;

void sensing_setup() {
    pinMode(IR_read, INPUT);
}

int sensing_readIRValue() {
    return analogRead(IR_read);
}

Color sensing_readLeftColor() {
    // TODO: Implement this function
    return {0, 0, 0};
}

Color sensing_readRightColor() {
    // TODO: Implement this function
    return {0, 0, 0};
}