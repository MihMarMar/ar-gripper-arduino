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

// reads data if there's something in the serial buffer 
void poll_serial(String &commandString){
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


// checks whether the item has fallen off unexpectedly
// returns 1 if fallen off, 0 otherwise
int is_item_fallen_off(){
  if (gripper.get_state() != S_CLOSED){
    return 0; // if arm isn't in closed state we don't care about pressure
  }

  // if there is still some pressure -> item has not fallen off
  // this assumes that the presure doesn't fluctuate a lot and stays constant
  // i.e. it will not go under 50 while item is still grabbed
  // otherwise a more complex way of checking can be added
  if (gripper.read_pressure() > 50){
    return 0; 
  }
  
  return 1; 
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  poll_serial(commandString);

  if(is_item_fallen_off()){
    gripper.open();
  }
  
}

  
