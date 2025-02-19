#include "Arm.h"

Arm::Arm()
{
	// Initializing Dynamixel2.0 Protocol Stuff for Differential A, B and Claw
	dyna = Dynamixel2Arduino(DYNAMIXEL_MOTORS_SERIAL, FULL_DUPLEX_DIR_PIN);

	// pinMode(WRIST_DIR_PIN,      OUTPUT); // OLD
	// pinMode(WRIST_SPEED_PIN,    OUTPUT); // OLD

	// Set used pins to output
	pinMode(SHOULDER_DIR_PIN, OUTPUT);
	pinMode(SHOULDER_SPEED_PIN, OUTPUT);
	pinMode(BASE_DIR_PIN, OUTPUT);
	pinMode(BASE_SPEED_PIN, OUTPUT);
	pinMode(ELBOW_DIR_PIN, OUTPUT);
	pinMode(ELBOW_SPEED_PIN, OUTPUT);

	// Initialize and start timer to outut correct PWM signals
	Timer3.initialize(time);
	Timer3.start();
}

Arm::~Arm()
{
	// Stop timer
	Timer3.stop();
}

void Arm::startUp()
{
	Timer3.stop();
	Timer3.initialize(time);
	Timer3.start();

	dyna.torqueOn(CLAW);
	dyna.torqueOn(DIFFERENCIAL_A);
	dyna.torqueOn(DIFFERENCIAL_B);
}

// pwm controls

void Arm::moveShoulder(Direction direction)
{

	// if disabled then end function
	if (m_disabled)
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
		Timer3.pwm(SHOULDER_SPEED_PIN, FIFTY_PERCENT_DUTY_CYCLE);
	}
	// If direction is OFF, stop motor
	else if (direction == OFF)
	{
		Timer3.pwm(SHOULDER_SPEED_PIN, 0);
	}
}

void Arm::moveBase(Direction direction)
{

	// if disabled then end function
	if (m_disabled)
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
		digitalWrite(BASE_DIR_PIN, (int)direction);
		Timer3.pwm(BASE_SPEED_PIN, FIFTY_PERCENT_DUTY_CYCLE);
	}
	// If direction is OFF, stop motor
	else if (direction == OFF)
	{
		Timer3.pwm(BASE_SPEED_PIN, 0);
	}
}

void Arm::moveElbow(Direction direction)
{
	// if disabled then end function
	if (m_disabled)
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

// void Arm::moveWrist(Direction direction)
// {
//   // if disabled then end function
//   if(m_disabled){return;}

//   // If direction is not OFF, move motor
//   if(direction != OFF)
//   {
//     #if ENABLE_SERIAL
//     Serial.println("Moving wrist");
//     #endif
//     // Write direction, HIGH is one way LOW is the other
//     digitalWrite(WRIST_DIR_PIN, (int)direction);
//     Timer3.pwm(WRIST_SPEED_PIN, 511);
//   }
//   // If direction is OFF, stop motor
//   else if(direction == OFF)
//   {
//     Timer3.pwm(WRIST_SPEED_PIN, 0);
//   }
// }

// dynamixel 2.0 controls

void Arm::moveClaw(Direction direction)
{
	// if disabled then end function
	if (m_disabled)
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

void Arm::bendWrist(Direction direction)
{
	// return if disabled
	if (m_disabled)
	{
		return;
	}

	if (direction == FORWARD)
	{
#if ENABLE_SERIAL
		Serial.println("Bending Wrist Forward");
#endif
		dyna.setGoalPWM(DIFFERENCIAL_A, diffAPercentSpeed, UNIT_PERCENT);
		dyna.setGoalPWM(DIFFERENCIAL_B, diffBPercentSpeed, UNIT_PERCENT);
		dyna.torqueOn(DIFFERENCIAL_A);
		dyna.torqueOn(DIFFERENCIAL_B);
	}
	else if (direction == REVERSE)
	{
#if ENABLE_SERIAL
		Serial.println("Bending Wrist Reverse");
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

void Arm::twistWrist(Direction direction)
{
	// return if disabled
	if (m_disabled)
	{
		return;
	}

	if (direction == FORWARD)
	{
#if ENABLE_SERIAL
		Serial.println("Twist Wrist 'Forward'");
#endif
		dyna.setGoalPWM(DIFFERENCIAL_A, diffAPercentSpeed, UNIT_PERCENT);
		dyna.setGoalPWM(DIFFERENCIAL_B, diffBPercentSpeed * -1, UNIT_PERCENT);
		dyna.torqueOn(DIFFERENCIAL_A);
		dyna.torqueOn(DIFFERENCIAL_B);
	}
	else if (direction == REVERSE)
	{
#if ENABLE_SERIAL
		Serial.println("Twist Wrist 'Reverse'");
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

// others

// void Arm::moveArm(Direction shoulderDirection, Direction wristDirection, Direction elbowDirection, Direction clawDirection)
// {
//   moveShoulder(shoulderDirection);
//   // moveWrist(wristDirection);
//   moveBase(elbowDirection);
//   moveClaw(clawDirection);
// }

void Arm::disable()
{
	moveBase(OFF);
	moveShoulder(OFF);
	moveElbow(OFF);
	dyna.torqueOff(DIFFERENCIAL_A);
	dyna.torqueOff(DIFFERENCIAL_B);
	dyna.torqueOff(CLAW);
	m_disabled = true;
}

bool Arm::changeDynamixelMotorID(uint8_t oldId, uint8_t newId)
{
	return dyna.setID(oldId, newId);
}
