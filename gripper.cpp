#include "gripper.h"

Gripper::Gripper(int servo_pin, int pressure_pin, int max_pressure, int max_angle){
    this->servo_pin = servo_pin;
    this->pressure_pin = pressure_pin;
    this->max_pressure = max_pressure;
    this->max_angle = max_angle;
    this->servo_pos = 90;  
    pinMode(pressure_pin, INPUT); 
    this->servo.attach(servo_pin);
    c_state = S_INITIALIZATION;
}

state Gripper::get_state(){
    return c_state; 
}

const String Gripper::read_ur5()
{
    char  received_char;
    received_char = 'u';
    if(Serial.available())
    {
      received_char = Serial.read();
      switch (received_char)
      {
        case 'a':
        {
          return "grip";
          break;
        }
  
        case 'b':
        {
          return "release";
          break;
        }
  
        case 'c':
        {
          return "reset";
          break;
        }

        case 'd':
        {
          return "sensor";
          break;
        }
  
        default:
        {
          return "unknown";
          break;
        }
      }
    }

    return "no message";
}

void Gripper::signal_ur5(const String& message)
{
  Serial.println(message);
}

void Gripper::work()
{
  switch(this->c_state)
  {
    case S_INITIALIZATION:
    {
      initializing();
      delay(100);
      break;
    }

    case S_IDLE:
    {
      idling();
      delay(100);
      break;
    }

    case S_CLOSING:
    {
      Serial.println("closing");
      closing();
      break;
    }

    case S_HOLDING:
    {
      Serial.println("holding");
      holding();
      break;
    }

    case S_PARTIAL_OPEN:
    {
      Serial.println("partial open");
      partial_open();
      break;
    }

    case S_END:
    {
      Serial.println("ending");
      end_tasking();
      break;
    }

    default:
    {
      Serial.println("unknown");
      break;
    }
  }
}

void Gripper::initializing()
{ // assumes that arm closes at higher angle
    //check angle threshold 
    //drive servo
    Serial.print("initializing ");
    Serial.println(this->servo_pos);
    this->servo_pos --;
    if(this->servo_pos > 0)
    {
      //opening
      this->servo.write(this->servo_pos);
    }
    else
    {
      //TODO: signal UR5
      signal_ur5("Gripper initialized");
      this->c_state = S_IDLE;
    }
}

void Gripper::idling()
{ // assumes that arm closes at higher angle
    //wait for ur5 signal to start
    //changing state
    Serial.println("idling ");
    //TODO wait for ur5 signal
    if(read_ur5() == "grip")
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
      signal_ur5("Object gripped");
      this->c_state = S_HOLDING;
      delay(500);
    }
}

void Gripper::holding()
{
  //check ur5 signal command
  //check pressure
  
  //ur5 command not received and gripper still holding the object
  String ur5_str = read_ur5();
  
  if(ur5_str != "release" && this->current_pressure >=0) 
  {
    //do nothing
    Serial.println(current_pressure);
  }
  //received ur5 command
  else if(ur5_str == "release")
  {
    // go to partial opening
    Serial.println("arm in placing position ");
    this->c_state = S_PARTIAL_OPEN;
  }
  else
  {
    // go to end
    Serial.println(ur5_str);
    this->c_state = S_END;
  }
  delay(500);
}

void Gripper::partial_open()
{ 
  //open until sensor read 0
 String ur5_str = read_ur5();
  if(this->read_pressure() >= 0 && ur5_str != "sensor")
  {
    //opening
    this->servo_pos --;
    servo.write(this->servo_pos);
    delay(20);
  }
  else
  {
    signal_ur5("Object placed");
    this->c_state = S_END;
    delay(500);
  }
}

void Gripper::end_tasking()
{ 
  //check for ur5 signal
  //if the signal was received
  if(read_ur5() == "reset")
  {
    this->servo_pos = 50;
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
