#include "main.h"

#include <Arduino.h>
#include <Tic.h>
#include <Servo.h>

// Auger vertical movement
const int switchOnPin = 12;
const int switchOffPin = 23;
const int AUGER_SPEED = 15000000;
TicI2C tic(15);
int augerUp, augerDown;

// Auger sampling
Servo drillMotor;
const int buttonPin = 11;
const int drillMotorPin = 7;
const int midPoint = 1500;
const int drillSpeed = 50;

void setup() {
    Serial.begin(9600);
    pinMode(switchOnPin, INPUT_PULLUP);
    pinMode(switchOffPin, INPUT_PULLUP);
    pinMode(buttonPin, INPUT_PULLDOWN);
    Wire.begin();
    delay(20);
    tic.exitSafeStart();
    drillMotor.attach(drillMotorPin);
}

void changeHeight() {
    augerUp = digitalRead(switchOnPin);
    augerDown = digitalRead(switchOffPin);
    if (augerUp == LOW) {
        tic.setTargetVelocity(AUGER_SPEED);
        // Serial.println("Moving up");
    }
    else if (augerDown == LOW) {
        tic.setTargetVelocity(-AUGER_SPEED);
        // Serial.println("Moving down");
    }
    else {
        tic.setTargetVelocity(0);
        // Serial.println("Idle");
    }
}

void takeSample() {
    int isSpinning = digitalRead(buttonPin);
    if (isSpinning == HIGH) {
        drillMotor.write(midPoint + drillSpeed);
        // Serial.println("Auging");
    }
    else {
        drillMotor.write(midPoint);
        // Serial.println("Not auging :(");
    }
}

void loop() {
    changeHeight();
    tic.resetCommandTimeout();		// Must be called at least once per second
    takeSample();
}

/**
 * Main setup for CAN idea
 */
 // void setup()
 // {
 // 	*can = CAN(&currentRunCycle);
 // 	can->startCAN();
 // }

 // void loop()
 // {
 // 	if (can->isNewMessage(CAN::E_STOP))
 // 	{

 // 	}
 // 	for (int i = 20; i < 22; ++i)
 // 	{
 // 		if (can->isNewMessage((CAN::Message_ID)i))
 // 		{
 // 			switch (i)
 // 			{
 // 			case 20:
 // 				break;
 // 			case 21:
 // 				break;
 // 			default:
 // 				Serial.printf("message type not accounted for %d\n", i);
 // 				break;
 // 			}
 // 		}
 // 	}
 // }
