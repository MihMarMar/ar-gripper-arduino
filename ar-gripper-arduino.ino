#include "gripper.h"

//TODO:: add feedback to the arm through Serial

#define MAX_PRESSURE_TRESHOLD 1000

// pin numbers 
#define SERVO_PIN 9
#define PRESSURE_SENSOR A0

Gripper gripper = Gripper(SERVO_PIN, PRESSURE_SENSOR, MAX_PRESSURE_TRESHOLD);

// checks whether the item has fallen off unexpectedly
// returns 1 if fallen off, 0 otherwise

void setup() {
  Serial.begin(115200);
}

void loop() 
{
  
}

  
