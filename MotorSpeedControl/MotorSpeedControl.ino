#include "motor_speed.h"
#include "sensing.h"
#include "state_machine.h"
#include "wifi_client.h"

#ifndef MOTOR_SPEED_H
#define MOTOR_SPEED_H


void setup() {
  Serial.begin(9600);
  motorspeed_setup();
  sensing_setup();
  // statemachine_setup();

  delay(100);
}

#define DEBUG_PRINT_COLOR(color_enum) {\
    if (color_enum == COLOR_RED) {\
      Serial.print("RED");\
    } else if (color_enum == COLOR_YELLOW) {\
      Serial.print("YELLOW");\
    } else if (color_enum == COLOR_BLUE) {\
      Serial.print("BLUE");\
    } else if (color_enum == COLOR_BLACK) {\
      Serial.print("BLACK");\
    }\
}

void loop() {
  // motorspeed_loop();
  sensing_loop();
  // statemachine_run();

  // wifi_sendmessage(String(sensing_readIRValue()));

  if (sensing_colorReady()) {
    SensorColor left = sensing_readLeftColor();
    SensorColor right = sensing_readRightColor();

    sensing_startColors();

    Serial.print("Left: ");
    DEBUG_PRINT_COLOR(left);
    Serial.println("");
    Serial.print("Right: ");
    DEBUG_PRINT_COLOR(right);
    Serial.println("");
  //   Serial.print("IR: ");
  //   Serial.println(sensing_readIRValue());
  //   Serial.println("");
  }

  delay(500);
}

#endif