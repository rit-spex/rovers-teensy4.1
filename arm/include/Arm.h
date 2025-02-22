#ifndef ARM_H
#define ARM_H

#include "Pinout.h"
#include "Constants.h"

#include <Arduino.h>
#include <TimerThree.h>
#include <TimerOne.h>
#include <Dynamixel2Arduino.h>

enum Direction
{
	FORWARD = 1,
	REVERSE = 0,
	OFF = 2
};

enum Dynamixel2MotorIDs
{
	DIFFERENCIAL_A = 1,
	DIFFERENCIAL_B = 2,
	CLAW = 3
};

void startUp();
void disable();
bool changeDynamixelMotorID(uint8_t oldID, uint8_t newID);
void moveBase(Direction direction);
void moveShoulder(Direction direction);
void moveElbow(Direction direction);
void moveClaw(Direction direction);
void bendWrist(Direction direction);
void twistWrist(Direction direction);

static bool is_disabled = false;
static Dynamixel2Arduino dyna;

static float diffAPercentSpeed = DYNAMIXEL_SPEED_PERCENT;
static float diffBPercentSpeed = DYNAMIXEL_SPEED_PERCENT;
static float clawPercentSpeed = DYNAMIXEL_SPEED_PERCENT;

// class Arm
// {
// public:
// 	enum Direction
// 	{
// 		FORWARD = 1,
// 		REVERSE = 0,
// 		OFF = 2
// 	};
// 	Arm();
// 	~Arm();
// 	void startUp();
// 	// functions to move the harmonic drives. These are the exact same but with different pin outputs
// 	// Functions work by setting timer output at either 50% duty cycle
// 	void moveShoulder(Direction direction);
// 	void moveElbow(Direction direction);
// 	void moveBase(Direction direction);
// 	void moveClaw(Direction direction);

// 	// void moveWrist(Direction direction); // OLD
// 	// doesn't work with new setup as their is no "moveWrist"
// 	// void moveArm(Direction shoulderDirection, Direction wristDirection, Direction baseDirection, Direction clawDirection);

// 	void disable();

// 	void bendWrist(Direction direction);
// 	void twistWrist(Direction direction);

// 	bool changeDynamixelMotorID(uint8_t oldId, uint8_t newId);

// 	// // stepper motor
// 	// TicI2C tic{CLAW_I2C_ID};
// private:
// 	// if disable flag is true then stop all arm motion and prevent the arm from moving
// 	bool m_disabled = false;

// 	// Changing this time will change the motor speeds 30 us seems to be a good starting speed
// 	int time = 80; // time in microseconds <- lower num mean faster fun

	// float diffAPercentSpeed = DYNAMIXEL_SPEED_PERCENT;

	// float diffBPercentSpeed = DYNAMIXEL_SPEED_PERCENT;

	// float clawPercentSpeed = DYNAMIXEL_SPEED_PERCENT;

	// Dynamixel2Arduino dyna;

// enum Dynamixel2MotorIDs
// {
// 	DIFFERENCIAL_A = 1,
// 	DIFFERENCIAL_B = 2,
// 	CLAW = 3
// };
// };

#endif
