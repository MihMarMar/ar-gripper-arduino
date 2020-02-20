#include "Arduino.h"
#include <Servo.h>

#define TX0 4
#define TX1 5
#define RX0 7
#define RX1 8

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
  unsigned int max_angle;
	unsigned int current_pressure; 

  unsigned long time_ms;
  bool          fsr_triggered;
	state c_state; 

  const String read_ur5_sim();

  void signal_ur5_sim(const String& message);

  const String read_ur5();

  void signal_ur5(const String& message);

  void initializing();

  void idling();
  
  void closing();

  void holding();

  void partial_open();

  void end_tasking();

  int read_pressure(); 

public: 
  Gripper::Gripper();
  
	Gripper(int servo_pin, int pressure_pin, int max_pressure, int max_angle);
  
  void work();
  
	void set_max_pressure(int);

  void test();
  
  state get_state();
}; 
