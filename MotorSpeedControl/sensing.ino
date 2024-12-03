/*
* Authors: Abe Nelson, Eric M. Rohloff
* Date: 12/3/2024
* 
* Function definitions color sensing. These functions encompass the color
* sensing logic for the bot. 
*/

#include "sensing.h"

const int IR_read = A0; // Pin to arduino
const int leftColorSensor = A1; // Pin to arduino 
const int rightColorSensor = A2; // Pin to arduino

// TODO: Define these pin numbers
const int redLed;
const int greenLed;
const int blueLed;

Color leftColor = {0, 0, 0};
int leftAmbient = 0;
bool leftReady = false;
Color rightColor = {0, 0, 0};
int rightAmbient = 0;
bool rightReady = false;

typedef enum {
    color_IDLE,
    color_READING_AMBIENT,
    color_READING_RED,
    color_READING_GREEN,
    color_READING_BLUE
} ColorState;

ColorState colorState = color_IDLE;

/*
* Function to set up the color sensing protocols and making sure each pin is
* initialized   
*/
void sensing_setup() {
    pinMode(IR_read, INPUT);
    pinMode(leftColorSensor, INPUT);
    pinMode(rightColorSensor, INPUT);
    pinMode(redLed, OUTPUT);
    pinMode(greenLed, OUTPUT);
    pinMode(blueLed, OUTPUT);

}

/*
* Function to set up the color sensing protocols and making sure each pin is
* initialized   
*/
void sensing_loop() {
    if (colorState == color_IDLE) {
        digitalWrite(redLed, LOW);
        digitalWrite(greenLed, LOW);
        digitalWrite(blueLed, LOW);
    
    } else if (colorState == color_READING_AMBIENT) {
        digitalWrite(redLed, LOW);
        digitalWrite(greenLed, LOW);
        digitalWrite(blueLed, LOW);

        leftAmbient = analogRead(leftColorSensor);
        rightAmbient = analogRead(rightColorSensor);

        colorState = color_READING_RED;

    } else if (colorState == color_READING_RED) {
        digitalWrite(redLed, HIGH);
        digitalWrite(greenLed, LOW);
        digitalWrite(blueLed, LOW);

        leftColor.red = analogRead(leftColorSensor) - leftAmbient;
        rightColor.red = analogRead(rightColorSensor) - rightAmbient;
        
        colorState = color_READING_GREEN;
    } else if (colorState == color_READING_GREEN) {
        digitalWrite(redLed, LOW);
        digitalWrite(greenLed, HIGH);
        digitalWrite(blueLed, LOW);

        leftColor.green = analogRead(leftColorSensor) - leftAmbient;
        rightColor.green = analogRead(rightColorSensor) - rightAmbient;

        colorState = color_READING_BLUE;
    } else if (colorState == color_READING_BLUE) {
        digitalWrite(redLed, LOW);
        digitalWrite(greenLed, LOW);
        digitalWrite(blueLed, HIGH);

        leftColor.blue = analogRead(leftColorSensor) - leftAmbient;
        rightColor.blue = analogRead(rightColorSensor) - rightAmbient;
        
        colorState = color_IDLE;
    }
}

int sensing_readIRValue() {
    return analogRead(IR_read);
}


/*
 * Determine if the color sensor should be line following or not
*/
bool sensing_colorReady() {
    return colorState == color_IDLE;
}

/*
 * Start reading values for each color
*/
void sensing_readColors() {
    colorState = color_READING_AMBIENT;
}

/*
 * Read from the left color sensor
*/
Color sensing_readLeftColor() {
    Serial.print("Left Color: ");
    Serial.print(leftColor.red);
    Serial.print(" ");
    Serial.print(leftColor.green);
    Serial.print(" ");
    Serial.println(leftColor.blue);
    return leftColor;
}

/*
 * Read from right color sensor
*/
Color sensing_readRightColor() {
    Serial.print("Right Color: ");
    Serial.print(rightColor.red);
    Serial.print(" ");
    Serial.print(rightColor.green);
    Serial.print(" ");
    Serial.println(rightColor.blue);
    return rightColor;
}