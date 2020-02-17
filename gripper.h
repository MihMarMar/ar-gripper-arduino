#include "Arduino.h"
#include <Servo.h>

enum state {
            S_INITIALIZATION,   //initializing gripper
            S_IDLE,             // gripper is idle state
        	  S_CLOSING,          // arm is closing/grabbing item
        	  S_HOLDING,          // arm has currently grabbed an item 
            S_PARTIAL_OPEN,     // gripper is partially opening 
        	  S_END};             // gripper signal UR5 to reset its 

class Gripper {
private: 
	Servo servo; 
	int servo_pin;
	int pressure_pin;
	unsigned int servo_pos; 
	unsigned int max_pressure;
	unsigned int current_pressure; 
	state c_state; 

  void initializing();

  void idling();
  
  void closing();

  void holding();

  void partial_open();

  void end_tasking();

  int read_pressure(); 

public: 
	Gripper(int servo_pin, int pressure_pin, int max_pressure);
  
  void work();
  
	void set_max_pressure(int);
  
  state get_state();
}; 
