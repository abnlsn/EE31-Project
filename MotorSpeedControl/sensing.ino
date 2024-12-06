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
const int redLed = 11;
const int greenLed = 12; // TODO: yellow
const int blueLed = 13;
const int irLed = 7;


// Variable Definitions
Color leftColor = {0, 0, 0};
int leftAmbient = 0;
bool leftReady = false;
Color rightColor = {0, 0, 0};
int rightAmbient = 0;
bool rightReady = false;

int irAmbient = 0;
int irValue = 0;

// Define Color States
typedef enum {
    color_IDLE,
    color_READING_AMBIENT,
    color_READING_RED,
    color_READING_GREEN,
    color_READING_BLUE
} ColorState;

// Define IR States
typedef enum {
    ir_READING_AMBIENT,
    ir_READING_VALUE,
} IRState;

ColorState colorState = color_IDLE;
IRState irState = ir_READING_AMBIENT;

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
    pinMode(irLed, OUTPUT);
}

/*
* Function to set up the color sensing protocols and making sure each pin is
* initialized   
*/
void sensing_loop() {
    if (irState == ir_READING_AMBIENT) {
        irAmbient = analogRead(IR_read);
        irState = ir_READING_VALUE;
        digitalWrite(irLed, LOW);
    } else if (irState == ir_READING_VALUE) {
        irValue = analogRead(IR_read) - irAmbient;
        irState = ir_READING_AMBIENT;
        digitalWrite(irLed, HIGH);
    }

    if (colorState == color_IDLE) {
        digitalWrite(redLed, LOW);
        digitalWrite(greenLed, LOW);
        digitalWrite(blueLed, LOW);
    
    } else if (colorState == color_READING_AMBIENT) {
        digitalWrite(redLed, LOW);
        digitalWrite(greenLed, LOW);
        digitalWrite(blueLed, LOW);

        Serial.print("Ambient: ");
        Serial.print(analogRead(leftColorSensor));
        Serial.print(" ");
        Serial.println(analogRead(rightColorSensor));

        leftAmbient = 0;
        rightAmbient = 0;

        colorState = color_READING_RED;

    } else if (colorState == color_READING_RED) {
        digitalWrite(redLed, HIGH);
        digitalWrite(greenLed, LOW);
        digitalWrite(blueLed, LOW);

        delay(1);

        leftColor.red = analogRead(leftColorSensor) - leftAmbient;
        rightColor.red = analogRead(rightColorSensor) - rightAmbient;
        
        colorState = color_READING_GREEN;
    } else if (colorState == color_READING_GREEN) {
        digitalWrite(redLed, LOW);
        digitalWrite(greenLed, HIGH);
        digitalWrite(blueLed, LOW);

        delay(1);

        leftColor.green = analogRead(leftColorSensor) - leftAmbient;
        rightColor.green = analogRead(rightColorSensor) - rightAmbient;

        colorState = color_READING_BLUE;
    } else if (colorState == color_READING_BLUE) {
        digitalWrite(redLed, LOW);
        digitalWrite(greenLed, LOW);
        digitalWrite(blueLed, HIGH);

        delay(1);

        leftColor.blue = analogRead(leftColorSensor) - leftAmbient;
        rightColor.blue = analogRead(rightColorSensor) - rightAmbient;
        
        colorState = color_IDLE;
    }
}

/*
* Function to read the IR value for the wall
*/
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