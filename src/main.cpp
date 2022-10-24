//===================
// Using I2C to send and receive structs between two Arduinos
//   SDA is the data connection and SCL is the clock connection
//   On an Uno  SDA is A4 and SCL is A5
//   On an Mega SDA is 20 and SCL is 21
//   GNDs must also be connected
//===================

#include <Arduino.h>
#include <Wire.h>


// PIN OUT
const int motor_controller_arm_A_start_pin = 2;
const int motor_controller_arm_A_end_pin = 3;
const int motor_controller_arm_A_pause_pin = 4;
const int motor_controller_arm_A_enable_pin = 5;

const int motor_controller_arm_B_start_pin = 6;
const int motor_controller_arm_B_end_pin = 7;
const int motor_controller_arm_B_pause_pin = 8;
const int motor_controller_arm_B_enable_pin = 9;

const int motor_controller_rings_start_pin = 10;
const int motor_controller_rings_enable_pin = 11;
const int motor_controller_rings_pause_pin = 12;
const int motor_controller_rings_continue_pin = 13;

// data to be received needs to mirror what was sent from 

struct motorStruct {
    uint8_t arm_A_start;                 
    uint8_t arm_A_end;                   
    uint8_t arm_A_pause;                 
    uint8_t arm_A_enable;                
    uint8_t arm_B_start;                 
    uint8_t arm_B_end;                   
    uint8_t arm_B_pause;                 
    uint8_t arm_B_enable;                
    uint8_t arm_rings_start;             
    uint8_t arm_rings_enable;           
    uint8_t arm_rings_pause;            
    uint8_t arm_rings_continue;          
};

motorStruct motor;

bool newRxData = false;


        // I2C control stuff

const byte thisAddress = 9; // these need to be swapped for the other Arduino
const byte otherAddress = 8;



void showNewData() {

    Serial.print("This just in    ");
    Serial.print(motor.arm_A_start);
    Serial.print(' ');
    Serial.print(motor.arm_A_end);
    Serial.print(' ');
    Serial.println(motor.arm_A_pause);
}

//============

        // this function is called by the Wire library when a message is received
void receiveEvent(int numBytesReceived) {

    if (newRxData == false) {
            // copy the data to motor
        Wire.readBytes( (byte*) &motor, numBytesReceived);
        newRxData = true;
    }
    else {
            // dump the data
        while(Wire.available() > 0) {
            byte c = Wire.read();
        }
    }
}


//=================================

void setup() {
    Serial.begin(115200);
    Serial.println("\nStarting I2C Slave demo\n");

    // set up I2C
    Wire.begin(thisAddress); // join i2c bus
    Wire.onReceive(receiveEvent); // register event
}

//============

void loop() {

        // this bit checks if a message has been received
    if (newRxData == true) {
        showNewData();
        newRxData = false;
    }
}


//=============
