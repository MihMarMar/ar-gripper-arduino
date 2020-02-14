#include "gripper.h"

//TODO:: add feedback to the arm through Serial

#define MAX_PRESSURE_TRESHOLD 1000

// pin numbers 
#define SERVO_PIN 9
#define PRESSURE_SENSOR A0

// command delimiters
#define COM_BEGIN_CHAR '_'
#define COM_END_CHAR '#'

// commands to control the arm
#define COM_OPEN "OPEN"
#define COM_CLOSE "CLOSE"

Gripper gripper = Gripper(SERVO_PIN, PRESSURE_SENSOR, MAX_PRESSURE_TRESHOLD);

String commandString; // command buffer

void poll_serial(String &commandString){
  // a function to read data if there's something in the serial buffer 
  if (Serial.available()) {
    
    // get the new byte and save it to command string 
    char inChar = (char) Serial.read();
    commandString += inChar;
    
    // if the incoming character is a hashtag string is complete
    if (inChar == COM_END_CHAR) {
      Serial.println(commandString);
      command_gripper(commandString);
      commandString = "";
    }
  }
}

void command_gripper(String command){
  if (command.charAt(0) != COM_BEGIN_CHAR) {
    return;
  }

  if (command.substring(1, strlen(COM_OPEN)) == COM_OPEN) { 
    gripper.open();
    return;
  }

 if (command.substring(1, strlen(COM_CLOSE)) == COM_CLOSE) { 
    gripper.close();
    return; 
  }

  Serial.print("unrecognised command: ");
  Serial.println(command);
}


void setup() {
  Serial.begin(115200);
}

void loop() {
  poll_serial(commandString);
  
  
}

  
