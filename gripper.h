#include "Arduino.h"
#include <Servo.h>

#define MSG_ARM_CLOSING "Arm closing" //ToDo: change when arm communication protocol is figured out
#define MSG_ARM_CLOSED "Arm closed" 
#define MSG_ARM_OPENING "Arm opening"
#define MSG_ARM_OPENED "Arm opened"

enum state {S_OPEN,     // arm is fully open 
        	  S_CLOSING,  // arm is closing/grabbing item
        	  S_CLOSED,   // arm has currently grabbed an item 
        	  S_FAIL};    // item has fallen of unexpectedly

class Gripper {
private: 
	Servo servo; 
	int servo_pin;
	int pressure_pin;
	unsigned int servo_pos; 
	unsigned int max_pressure;
	unsigned int current_pressure; 
	state c_state; 
	int read_pressure(); 
public: 
	Gripper(int, int, int);

	state get_state();

	void close();

	void open();

	void set_max_pressure(int);

}; 
