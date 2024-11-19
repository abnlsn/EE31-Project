#include "sensing.h"

const int IR_read = A0;

void sensing_setup() {
    pinMode(IR_read, INPUT);
}

int sensing_readIRValue() {
    return analogRead(IR_read);
}