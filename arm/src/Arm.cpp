#include "Arm.h"

// Arm::Arm()
// {
// 	// Initializing Dynamixel2.0 Protocol Stuff for Differential A, B and Claw
// dyna = Dynamixel2Arduino(DYNAMIXEL_MOTORS_SERIAL, FULL_DUPLEX_DIR_PIN);

// 	// pinMode(WRIST_DIR_PIN,      OUTPUT); // OLD
// 	// pinMode(WRIST_SPEED_PIN,    OUTPUT); // OLD

// 	// Set used pins to output
// 	pinMode(SHOULDER_DIR_PIN, OUTPUT);
// 	pinMode(SHOULDER_SPEED_PIN, OUTPUT);
// 	pinMode(BASE_DIR_PIN, OUTPUT);
// 	pinMode(BASE_SPEED_PIN, OUTPUT);
// 	pinMode(ELBOW_DIR_PIN, OUTPUT);
// 	pinMode(ELBOW_SPEED_PIN, OUTPUT);

// 	// Initialize and start timer to outut correct PWM signals
// 	// Timer3.initialize(time);
// 	// Timer3.start();
// }

// Arm::~Arm()
// {
// 	// Stop timer
// 	Timer1.stop();
// 	Timer3.stop();
// }

// void Arm::startUp()
// {
// 	// Timer1.stop();
// 	// Timer1.initialize(time);
// 	// Timer1.start();

// 	Timer3.stop();
// 	Timer3.initialize(time);
// 	Timer3.start();

// dyna.torqueOn(CLAW);
// dyna.torqueOn(DIFFERENCIAL_A);
// dyna.torqueOn(DIFFERENCIAL_B);
// }

void startUp()
{
	pinMode(SHOULDER_DIR_PIN, OUTPUT);
	pinMode(SHOULDER_SPEED_PIN, OUTPUT);
	pinMode(BASE_DIR_PIN, OUTPUT);
	pinMode(BASE_SPEED_PIN, OUTPUT);
	pinMode(ELBOW_DIR_PIN, OUTPUT);
	pinMode(ELBOW_SPEED_PIN, OUTPUT);

	Timer1.initialize(TIME);
	Timer1.start();
	Timer3.initialize(TIME);
	Timer3.start();

	dyna = Dynamixel2Arduino(DYNAMIXEL_MOTORS_SERIAL, FULL_DUPLEX_DIR_PIN);
	dyna.setPortProtocolVersion(DYNAMIXEL_PROTOCOL_VERSION);
	dyna.begin(DYNAMIXEL_BAUD_RATE);
	printf("ping: %d\n", dyna.ping(1));
	dyna.torqueOn(CLAW);
	dyna.torqueOn(DIFFERENCIAL_A);
	dyna.torqueOn(DIFFERENCIAL_B);
}

void disable()
{
	moveBase(OFF);
	moveShoulder(OFF);
	moveElbow(OFF);
	dyna.torqueOff(DIFFERENCIAL_A);
	dyna.torqueOff(DIFFERENCIAL_B);
	dyna.torqueOff(CLAW);
	is_disabled = true;
}

bool changeDynamixelMotorID(uint8_t oldID, uint8_t newID)
{
	return dyna.setID(oldID, newID);
}

void moveShoulder(Direction direction)
{
	// if disabled then end function
	if (is_disabled)
	{
		return;
	}

	// If direction is not OFF, move motor
	if (direction != OFF)
	{
#if ENABLE_SERIAL
		Serial.println("Moving shoulder");
#endif
		// Write direction, HIGH is one way LOW is the other
		digitalWrite(SHOULDER_DIR_PIN, (int)direction);
		Timer1.pwm(SHOULDER_SPEED_PIN, FIFTY_PERCENT_DUTY_CYCLE);
	}
	// If direction is OFF, stop motor
	else if (direction == OFF)
	{
		Timer1.pwm(SHOULDER_SPEED_PIN, 0);
	}
}

void moveBase(Direction direction)
{
	Serial.println("gaming?");
	// if disabled then end function
	if (is_disabled)
	{
		Serial.println("shit is disabed");
		return;
	}

	// If direction is not OFF, move motor
	if (direction != OFF)
	{
#if ENABLE_SERIAL
		Serial.println("Moving base");
#endif
		// Write direction, HIGH is one way LOW is the other
		Serial.println("doing shit");
		digitalWrite(BASE_DIR_PIN, (int)direction);
		Timer3.pwm(BASE_SPEED_PIN, FIFTY_PERCENT_DUTY_CYCLE);
	}
	// If direction is OFF, stop motor
	else if (direction == OFF)
	{
		Serial.println("shit was off");
		Timer3.pwm(BASE_SPEED_PIN, 0);
	}
}

void newMoveBase(Direction direction)
{
	Serial.println("starting base");
	Serial.printf("direction: %d\n", direction);
	Serial.printf("duty_cycle: %d\n", FIFTY_PERCENT_DUTY_CYCLE);
	if (direction != OFF)
	{
		// Serial.println("writing to pins");
		Serial.println("TROLLING ON DIDDY!");
		digitalWrite(BASE_DIR_PIN, direction);
		Timer3.pwm(BASE_SPEED_PIN, FIFTY_PERCENT_DUTY_CYCLE);
	}
	else
	{
		Serial.println("stopping pins");
		Timer3.pwm(BASE_SPEED_PIN, 0);
	}
}

void moveElbow(Direction direction)
{
	// if disabled then end function
	if (is_disabled)
	{
		return;
	}

	// If direction is not OFF, move motor
	if (direction != OFF)
	{
#if ENABLE_SERIAL
		Serial.println("Moving base");
#endif
		// Write direction, HIGH is one way LOW is the other
		digitalWrite(ELBOW_DIR_PIN, (int)direction);
		Timer3.pwm(ELBOW_SPEED_PIN, FIFTY_PERCENT_DUTY_CYCLE);
	}
	// If direction is OFF, stop motor
	else if (direction == OFF)
	{
		Timer3.pwm(ELBOW_SPEED_PIN, 0);
	}
}

// dynamixel 2.0 controls

void moveClaw(Direction direction)
{
	// if disabled then end function
	if (is_disabled)
	{
		return;
	}

	if (direction == FORWARD)
	{
#if ENABLE_SERIAL
		Serial.println("Moving claw Forward");
#endif
		dyna.setGoalPWM(CLAW, clawPercentSpeed, UNIT_PERCENT);
		dyna.torqueOn(CLAW);
	}
	else if (direction == REVERSE)
	{
#if ENABLE_SERIAL
		Serial.println("Moving claw Reverse");
#endif
		dyna.setGoalPWM(CLAW, clawPercentSpeed * -1, UNIT_PERCENT);
		dyna.torqueOn(CLAW);
	}
	else if (direction == OFF)
	{
		dyna.torqueOff(CLAW);
	}
}

void bendWrist(Direction direction)
{
	// return if disabled
	if (is_disabled)
	{
		return;
	}

	if (direction == FORWARD)
	{
#if ENABLE_SERIAL
		Serial.println("Bending Wrist Forward");
#endif
		// opposite directions because the differentials face opposite directions on the arm
		dyna.setGoalPWM(DIFFERENCIAL_A, diffAPercentSpeed, UNIT_PERCENT);
		dyna.setGoalPWM(DIFFERENCIAL_B, diffBPercentSpeed * -1, UNIT_PERCENT);
		dyna.torqueOn(DIFFERENCIAL_A);
		dyna.torqueOn(DIFFERENCIAL_B);
	}
	else if (direction == REVERSE)
	{
#if ENABLE_SERIAL
		Serial.println("Bending Wrist Reverse");
#endif
		dyna.setGoalPWM(DIFFERENCIAL_A, diffAPercentSpeed * -1, UNIT_PERCENT);
		dyna.setGoalPWM(DIFFERENCIAL_B, diffBPercentSpeed, UNIT_PERCENT);
		dyna.torqueOn(DIFFERENCIAL_A);
		dyna.torqueOn(DIFFERENCIAL_B);
	}
	else if (direction == OFF)
	{
		dyna.torqueOff(DIFFERENCIAL_A);
		dyna.torqueOff(DIFFERENCIAL_B);
	}
}

void twistWrist(Direction direction)
{
	// return if disabled
	if (is_disabled)
	{
		return;
	}

	if (direction == FORWARD)
	{
#if ENABLE_SERIAL
		Serial.println("Twist Wrist 'Forward'");
#endif
		// same direction because the motors face differentials ways so they rotate the other way naturally
		dyna.setGoalPWM(DIFFERENCIAL_A, diffAPercentSpeed, UNIT_PERCENT);
		dyna.setGoalPWM(DIFFERENCIAL_B, diffBPercentSpeed, UNIT_PERCENT);
		dyna.torqueOn(DIFFERENCIAL_A);
		dyna.torqueOn(DIFFERENCIAL_B);
	}
	else if (direction == REVERSE)
	{
#if ENABLE_SERIAL
		Serial.println("Twist Wrist 'Reverse'");
#endif
		dyna.setGoalPWM(DIFFERENCIAL_A, diffAPercentSpeed * -1, UNIT_PERCENT);
		dyna.setGoalPWM(DIFFERENCIAL_B, diffBPercentSpeed * -1, UNIT_PERCENT);
		dyna.torqueOn(DIFFERENCIAL_A);
		dyna.torqueOn(DIFFERENCIAL_B);
	}
	else if (direction == OFF)
	{
		dyna.torqueOff(DIFFERENCIAL_A);
		dyna.torqueOff(DIFFERENCIAL_B);
	}
}

// others

// void Arm::moveArm(Direction shoulderDirection, Direction wristDirection, Direction elbowDirection, Direction clawDirection)
// {
//   moveShoulder(shoulderDirection);
//   // moveWrist(wristDirection);
//   moveBase(elbowDirection);
//   moveClaw(clawDirection);
// }
