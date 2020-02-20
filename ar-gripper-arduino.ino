#include "gripper.h"

#define MAX_PRESSURE_TRESHOLD 100
#define MAX_SERVO_THRESHOLD 120

// pin numbers 
#define SERVO_PIN 9
#define PRESSURE_SENSOR A0

Gripper gripper;
void setup() {
  Serial.begin(9600);
  gripper = Gripper(SERVO_PIN, PRESSURE_SENSOR, MAX_PRESSURE_TRESHOLD, MAX_SERVO_THRESHOLD);
}

void loop() 
{
  gripper.work();
}

  
