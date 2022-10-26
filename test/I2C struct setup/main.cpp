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
struct motor {
    uint8_t bottom;                 
    uint8_t top;                   
    uint8_t pause;                 
    uint8_t enable;                
};
struct motorRing{
    uint8_t start;             
    uint8_t enable;           
    uint8_t pause;            
    uint8_t resume;          
};

struct controllerStruct{
    motor armA;
    motor armB;
    motorRing rings;
};

controllerStruct controller;

bool newRxData = false;


// I2C control stuff

const byte thisAddress = 9; // these need to be swapped for the other Arduino
const byte otherAddress = 8;



void showNewData() {

    Serial.print("This just in    ");
    if (controller.armA.enable)
    {
        digitalWrite(motor_controller_arm_A_enable_pin, HIGH);
        Serial.print("controller.armA.enable: ");
        Serial.println(controller.armA.enable);
    }
    else if (!controller.armA.enable)
    {
        digitalWrite(motor_controller_arm_A_enable_pin, LOW);
        Serial.print("controller.armA.enable: ");
        Serial.println(controller.armA.enable);
    }
    
    if (controller.armB.enable)
    {
        digitalWrite(motor_controller_arm_B_enable_pin, HIGH);
        Serial.print("controller.armB.enable: ");
        Serial.println(controller.armB.enable);
    }
    else if (!controller.armB.enable)
    {
        digitalWrite(motor_controller_arm_B_enable_pin, LOW);
        Serial.print("controller.armB.enable: ");
        Serial.println(controller.armB.enable);
    }    Serial.print(' ');

    if (controller.rings.enable)
    {
        digitalWrite(motor_controller_rings_enable_pin, HIGH);
        Serial.print("controller.rings.enable: ");
        Serial.println(controller.rings.enable);
    }
    else if (!controller.rings.enable)
    {
        digitalWrite(motor_controller_rings_enable_pin, LOW);
        Serial.print("controller.rings.enable: ");
        Serial.println(controller.rings.enable);
    }
}
//============

        // this function is called by the Wire library when a message is received
void receiveEvent(int numBytesReceived) {

    if (newRxData == false) {
            // copy the data to motor
        Wire.readBytes( (byte*) &controller, numBytesReceived);
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
