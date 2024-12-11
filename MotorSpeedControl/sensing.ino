/*
* Authors: Abe Nelson, Eric M. Rohloff
* Date: 12/3/2024
* 
* Function definitions color sensing. These functions encompass the color
* sensing logic for the bot. 
*/

#include "sensing.h"

typedef struct {
    int r;
    int y;
    int b;
} Color;

const int IR_read = A5; // Pin to arduino
const int IR_transistor = A0;
const int leftColorSensor = A1; // Pin to arduino 
const int rightColorSensor = A2; // Pin to arduino

// TODO: Define these pin numbers
const int redLed = 7;
const int yellowLed = 8; // TODO: yellow
const int blueLed = 9;
const int irLed = 2;

Color leftColor = {0, 0, 0};
Color rightColor = {0, 0, 0};

// Range Values for the Color Sensor
#define LEFT_RED_LOW 320
#define LEFT_BLUE_LOW 280
#define LEFT_YELLOW_LOW 180

#define RIGHT_RED_LOW 115
#define RIGHT_BLUE_LOW 500
#define RIGHT_YELLOW_LOW 65

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
    pinMode(yellowLed, OUTPUT);
    pinMode(blueLed, OUTPUT);
    pinMode(irLed, OUTPUT);

    digitalWrite(irLed, HIGH);
    digitalWrite(IR_transistor, HIGH);

    delay(50);
    analogRead(IR_read);
    delay(50);
}

/*
* Function to set up the color sensing protocols and making sure each pin is
* initialized   
*/
void sensing_loop() {

    irValue = analogRead(IR_read);

    if (colorState == color_IDLE) {
        digitalWrite(redLed, LOW);
        digitalWrite(yellowLed, LOW);
        digitalWrite(blueLed, LOW);
    } else if (colorState == color_READING_RED) {
        digitalWrite(redLed, HIGH);
        digitalWrite(yellowLed, LOW);
        digitalWrite(blueLed, LOW);

        delay(1);

        leftColor.r = analogRead(leftColorSensor);
        rightColor.r = analogRead(rightColorSensor);

        colorState = color_READING_GREEN;
    } else if (colorState == color_READING_GREEN) {
        digitalWrite(redLed, LOW);
        digitalWrite(yellowLed, HIGH);
        digitalWrite(blueLed, LOW);

        delay(1);

        leftColor.y = analogRead(leftColorSensor);
        rightColor.y = analogRead(rightColorSensor);

        colorState = color_READING_BLUE;
    } else if (colorState == color_READING_BLUE) {
        digitalWrite(redLed, LOW);
        digitalWrite(yellowLed, LOW);
        digitalWrite(blueLed, HIGH);

        delay(1);

        leftColor.b = analogRead(leftColorSensor);
        rightColor.b = analogRead(rightColorSensor);

        
        colorState = color_IDLE;
    }
}

/*
* Function to read the IR value for the wall
*/
int sensing_readIRValue() {
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
    // Serial.print("Left Color: ");
    // Serial.print(leftColor.r);
    // Serial.print(" ");
    // Serial.print(leftColor.y);
    // Serial.print(" ");
    // Serial.println(leftColor.b);
    if (leftColor.r > LEFT_RED_LOW && leftColor.y < LEFT_YELLOW_LOW && leftColor.b < LEFT_BLUE_LOW) {
        return COLOR_RED;
    } else if (leftColor.b > LEFT_BLUE_LOW && leftColor.y < LEFT_YELLOW_LOW) {
        return COLOR_BLUE;
    } else if (leftColor.y > LEFT_YELLOW_LOW) {
        return COLOR_YELLOW;
    } else {
        return COLOR_BLACK;
    }
}

SensorColor getColorRight(int sum) {
    // Serial.print("Right Color: ");
    // Serial.print(rightColor.r);
    // Serial.print(" ");
    // Serial.print(rightColor.y);
    // Serial.print(" ");
    // Serial.println(rightColor.b);
    if (rightColor.r > RIGHT_RED_LOW && rightColor.y < RIGHT_YELLOW_LOW && rightColor.b < RIGHT_BLUE_LOW) {
        return COLOR_RED;
    } else if (rightColor.b > RIGHT_BLUE_LOW && rightColor.y < RIGHT_YELLOW_LOW) {
        return COLOR_BLUE;
    } else if (rightColor.y > RIGHT_YELLOW_LOW) {
        return COLOR_YELLOW;
    } else {
        return COLOR_BLACK;
    }
}

/*
 * Read from the left color sensor
*/
SensorColor sensing_readLeftColor() {
    SensorColor left = getColorLeft(leftColorSum);
    Serial.print("Left: ");
    DEBUG_PRINT_COLOR(left);
    Serial.println("");
    return left;
}

/*
 * Read from right color sensor
*/
SensorColor sensing_readRightColor() {
    SensorColor right = getColorRight(rightColorSum);
    Serial.print("Right: ");
    DEBUG_PRINT_COLOR(right);
    Serial.println("");
    return right;
}