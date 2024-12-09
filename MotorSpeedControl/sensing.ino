/*
* Authors: Abe Nelson, Eric M. Rohloff
* Date: 12/3/2024
* 
* Function definitions color sensing. These functions encompass the color
* sensing logic for the bot. 
*/

#include "sensing.h"

const int IR_read = A5; // Pin to arduino
const int IR_transistor = A0;
const int leftColorSensor = A1; // Pin to arduino 
const int rightColorSensor = A2; // Pin to arduino

// TODO: Define these pin numbers
const int redLed = 7;
const int greenLed = 8; // TODO: yellow
const int blueLed = 9;
const int irLed = 2;

// Range Values for the Color Sensor
#define LEFT_RED_HIGH 250
#define LEFT_RED_LOW 90
#define LEFT_BLUE_HIGH 809
#define LEFT_BLUE_LOW LEFT_RED_HIGH
#define LEFT_YELLOW_LOW 810
#define LEFT_YELLOW_HIGH 1200

#define RIGHT_RED_HIGH 180
#define RIGHT_RED_LOW 90
#define RIGHT_BLUE_HIGH 600
#define RIGHT_BLUE_LOW 300
#define RIGHT_YELLOW_LOW (RIGHT_BLUE_HIGH)
#define RIGHT_YELLOW_HIGH 1200

// Variable Definitions
int leftColorSum = 0;
int leftAmbient = 0;

int rightColorSum = 0;
int rightAmbient = 0;


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
    pinMode(IR_transistor, OUTPUT);
    pinMode(leftColorSensor, INPUT);
    pinMode(IR_read, INPUT);
    pinMode(rightColorSensor, INPUT);
    pinMode(redLed, OUTPUT);
    pinMode(greenLed, OUTPUT);
    pinMode(blueLed, OUTPUT);
    pinMode(irLed, OUTPUT);

    digitalWrite(irLed, HIGH);
    digitalWrite(IR_transistor, HIGH);
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
    } else if (colorState == color_READING_RED) {
        digitalWrite(redLed, HIGH);
        digitalWrite(greenLed, LOW);
        digitalWrite(blueLed, LOW);

        delay(1);

        leftColorSum = analogRead(leftColorSensor);
        rightColorSum = analogRead(rightColorSensor);
        
        colorState = color_READING_GREEN;
    } else if (colorState == color_READING_GREEN) {
        digitalWrite(redLed, LOW);
        digitalWrite(greenLed, HIGH);
        digitalWrite(blueLed, LOW);

        delay(1);

        leftColorSum += analogRead(leftColorSensor);
        rightColorSum += analogRead(rightColorSensor);

        colorState = color_READING_BLUE;
    } else if (colorState == color_READING_BLUE) {
        digitalWrite(redLed, LOW);
        digitalWrite(greenLed, LOW);
        digitalWrite(blueLed, HIGH);

        delay(1);

        leftColorSum = analogRead(leftColorSensor);
        rightColorSum = analogRead(rightColorSensor);
        
        colorState = color_IDLE;
    }
}

/*
* Function to read the IR value for the wall
*/
int sensing_readIRValue() {
    irValue = analogRead(IR_read);
    return irValue;
    // return 0;
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
void sensing_startColors() {
    colorState = color_READING_RED;
}

SensorColor getColorLeft(int sum) {
    if (sum > LEFT_RED_LOW && sum < LEFT_RED_HIGH) {
        return COLOR_RED;
    } else if (sum > LEFT_BLUE_LOW && sum < LEFT_BLUE_HIGH) {
        return COLOR_BLUE;
    } else if (sum > LEFT_YELLOW_LOW && sum < LEFT_YELLOW_HIGH) {
        return COLOR_YELLOW;
    } else {
        return COLOR_BLACK;
    }
}

SensorColor getColorRight(int sum) {
    if (sum > RIGHT_RED_LOW && sum < RIGHT_RED_HIGH) {
        return COLOR_RED;
    } else if (sum > RIGHT_BLUE_LOW && sum < RIGHT_BLUE_HIGH) {
        return COLOR_BLUE;
    } else if (sum > RIGHT_YELLOW_LOW && sum < RIGHT_YELLOW_HIGH) {
        return COLOR_YELLOW;
    } else {
        return COLOR_BLACK;
    }
}

/*
 * Read from the left color sensor
*/
SensorColor sensing_readLeftColor() {
    Serial.print("Left Color: ");
    Serial.println(leftColorSum);
    return getColorLeft(leftColorSum);
}

/*
 * Read from right color sensor
*/
SensorColor sensing_readRightColor() {
    Serial.print("Right Color: ");
    Serial.println(rightColorSum);
    return getColorRight(rightColorSum);
}