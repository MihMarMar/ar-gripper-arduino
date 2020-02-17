#include "gripper.h"

Gripper::Gripper(int servo_pin, int pressure_pin, int max_pressure){
    this->servo_pin = servo_pin;
    this->pressure_pin = pressure_pin;
    this->max_pressure = max_pressure;
    this->servo_pos = 0;  
    pinMode(pressure_pin, INPUT); 
    servo.attach(servo_pin);
    c_state = S_INITIALIZATION;
}

state Gripper::get_state(){
    return c_state; 
}

void Gripper::work()
{
  
}

void Gripper::initializing()
{ // assumes that arm closes at higher angle
    //check angle threshold 
    //drive servo
    
    if(this->servo_pos > 0)
    {
      //opening
      servo.write(--servo_pos);
      delay(20);
    }
    else
    {
      //signal the UR5
      //changing state
      
      //TODO: signal UR5
      this->c_state = S_IDLE;
    }
}

void Gripper::idling()
{ // assumes that arm closes at higher angle
    //wait for ur5 signal to start
    //changing state
    
    //TODO wait for ur5 signal
    if(false)
    {
      this->c_state = S_CLOSING;
    }
}

void Gripper::closing()
{ // assumes that arm closes at higher angle
    //check pressure
    //check angle threshold 
    //drive servo

    read_pressure();
    if(this->current_pressure < this->max_pressure && this->servo_pos < 180)
    {
      //closing
      servo.write(++servo_pos);
      delay(20);
    }
    else
    {
      //changing state
      this->c_state = S_HOLDING;
    }
}

void Gripper::holding()
{
  //check ur5 signal command
  //check pressure

  //TODO check ur5 signal command
  
  //ur5 command not received and gripper still holding the object
  if(false == false && this->current_pressure >0) 
  {
    //do nothing
  }
  //received ur5 command
  else if(false == true)
  {
    // go to partial opening
    this->c_state = S_PARTIAL_OPEN;
  }
  else
  {
    // go to end
    this->c_state = S_END;
  }
}

void Gripper::partial_open()
{ 
  //open until sensor read 0
  if(this->servo_pos > 0)
  {
    //opening
    servo.write(--servo_pos);
    delay(20);
  }
  else
  {
    this->c_state = S_END;
  }
}

void Gripper::end_tasking()
{ 
  //check for ur5 signal

  //TODO check for ur5 signal
  //if the signal was received
  if(false == false)
  {
    this->c_state = S_INITIALIZATION;
  }
}

void Gripper::set_max_pressure(int max_pressure){
    /*this->max_pressure = max_pressure; */
}

int Gripper::read_pressure(){
    this->current_pressure = analogRead(pressure_pin);
    return this->current_pressure;
}
