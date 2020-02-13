#include "gripper.h"

// pin numbers 
#define SERVO_PIN 9
#define PRESSURE_SENSOR A0

// command delimiters
#define COM_BEGIN_CHAR '_'
#define COM_END_CHAR '#'

Gripper gripper = Gripper(SERVO_PIN, PRESSURE_SENSOR, 1000);

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

  if (command.substring(1, 4) == "OPEN") { 
    gripper.open();
    return;
  }

  if (command.substring(1, 4) == "CLOSE") { 
    gripper.close();
    return; 
  }

  Serial.print("unrecognised command: ");
  Serial.println(command);
}


String commandString; // command buffer

void setup() {
  Serial.begin(115200);
}

void loop() {
  poll_serial(commandString);

}

  
