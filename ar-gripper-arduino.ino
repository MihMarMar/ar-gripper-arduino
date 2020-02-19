#include "gripper.h"
#include <Servo.h>

#define MAX_PRESSURE_TRESHOLD 900
#define MAX_SERVO_THRESHOLD 180

// pin numbers 
#define SERVO_PIN 9
#define PRESSURE_SENSOR A0

Gripper gripper = Gripper(SERVO_PIN, PRESSURE_SENSOR, MAX_PRESSURE_TRESHOLD, MAX_SERVO_THRESHOLD);

void setup() {
  Serial.begin(9600);

}

void loop() 
{
  gripper.work();
  
}

  
