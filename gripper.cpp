#include "gripper.h"

Gripper::Gripper(int servo_pin, int pressure_pin, int max_pressure){
    this->servo_pin = servo_pin;
    this->pressure_pin = pressure_pin;
    this->max_pressure = max_pressure;
    this->servo_pos = 0;  
    pinMode(pressure_pin, INPUT); 
    servo.attach(servo_pin);
    c_state = S_OPEN;
}

state Gripper::get_state(){
    return c_state; 
}

void Gripper::close(){ // assumes that arm closes at higher angle
    c_state = S_CLOSING;
    Serial.println(MSG_ARM_CLOSING);
    while (read_pressure() < max_pressure){
        servo.write(++servo_pos);
        delay(10); // give time for the servo 
                   // to go into the set positon
                   // and the pressure reading to stabilize 
    }
    Serial.print(MSG_ARM_CLOSED);
    c_state = S_CLOSED;  
}

void Gripper::open(){
    Serial.print(MSG_ARM_OPENING);
    do {
        servo.write(--servo_pos);
        delay(5); // slow it down
    } while (servo_pos > 0);
    c_state = S_OPEN;
    Serial.print(MSG_ARM_OPENED);
}

void Gripper::fail(){ // same as open(), but signals fault instead
    do {
        servo.write(--servo_pos);
        delay(5); // slow it down
    } while (servo_pos > 0);
    c_state = S_OPEN;
    Serial.println(MSG_FAIL);
}


void Gripper::set_max_pressure(int max_pressure){
    this->max_pressure = max_pressure; 
}

int Gripper::read_pressure(){
    this->current_pressure = analogRead(pressure_pin);
    return this->current_pressure; 
}
