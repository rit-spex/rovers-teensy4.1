// Debugging
#define ENABLE_SERIAL 1

#include "memory"

#include <Arduino.h>
#include "Arm.h"
#include <Dynamixel2Arduino.h>
#include "CAN.h"

#include "Pinout.h"
#include "Constants.h"

// static Arm *arm;
unsigned long currentRunCycle = 0;
// CAN *can;
std::shared_ptr<CAN> can;
Dynamixel2Arduino dyna(DYNAMIXEL_MOTORS_SERIAL, FULL_DUPLEX_DIR_PIN);

void setup()
{
// #if ENABLE_SERIAL
	Serial.begin(9600);
	Serial.println("Arm");
	delay(1000);
// #endif
	startUp(dyna);

	can = std::make_shared<CAN>(&currentRunCycle);
	// *can = CAN(&currentRunCycle);
	can->startCAN();
}

void loop()
{
	// need to call this to read and "sniff" each message
	can->readMsgBuffer();
	if (can->isNewMessage(CAN::ARM_E_STOP))
	{
		disable(dyna);
	}
	for (int i = 10; i < 16; ++i)
	{
		if (can->isNewMessage((CAN::Message_ID)i))
		{
			// declare arm specific function variable on the stack with param of Direction
			// void (*func)(Direction);
			uint8_t *data;
			data = can->getUnpackedData((CAN::Message_ID)i);
			Serial.printf("ID %d: %p", i, data);
			Direction direction = (Direction)data[1];
			if (!data[0])
			{
				direction = OFF;
			}
			switch (i)
			{
			case 11:
				// sets func variable to the correct arm function based on the can message id thats new
				// func = &moveBase;
				moveBase(direction);
				break;
			case 12:
				// func = &moveShoulder;
				moveShoulder(direction);
				break;
			case 13:
				// func = &moveElbow;
				moveElbow(direction);
				break;
			case 14:
				// func = &bendWrist;
				bendWrist(dyna, direction);
				break;
			case 15:
				// func = &twistWrist;
				twistWrist(dyna, direction);
				break;
			case 16:
				// func = &moveClaw;
				moveClaw(dyna, direction);
				break;
			case 17:
				moveSolenoid(data[0]);
				break;
			default:
#if ENABLE_SERIAL
				Serial.printf("message type not accounted for %d\n", i);
#endif
				disable(dyna);
				break;
			}
			// if the message at index 0 is 1, then that part of the arm will stop
			// if (can->getUnpackedMessage((CAN::Message_ID)i, 0))
			// {
			// 	(*func)(Direction::OFF);
			// }
			// else
			// {
			// 	// if the message at index 1 is 0, it will move in reverse, if the message is 1, then it will move forward
			// 	(*func)(static_cast<Direction>(can->getUnpackedMessage((CAN::Message_ID)i, 1)));
			// }
		}
	}

	/* Test */
	// Serial.println("base");
	// moveBase(Direction::FORWARD);
	// delay(200);
	// moveBase(Direction::REVERSE);
	// delay(200);
	// moveBase(Direction::OFF);
	// delay(3000);
	// Serial.println("start of shoulder");
	// moveShoulder(Direction::FORWARD);
	// delay(200);
	// moveShoulder(Direction::REVERSE);
	// delay(200);
	// moveShoulder(Direction::OFF);
	// delay(3000);
	// Serial.println("start of elbow");
	// moveElbow(Direction::FORWARD);
	// delay(200);
	// moveElbow(Direction::REVERSE);
	// delay(200);
	// moveElbow(Direction::OFF);
	// delay(3000);
	// Serial.println("start of twist wrist");
	// twistWrist(Direction::FORWARD);
	// delay(200);
	// twistWrist(Direction::REVERSE);
	// delay(200);
	// twistWrist(Direction::OFF);
	// delay(3000);
	// Serial.println("start of bend wrist");
	// bendWrist(Direction::FORWARD);
	// delay(200);
	// bendWrist(Direction::REVERSE);
	// delay(200);
	// bendWrist(Direction::OFF);
	// delay(3000);
	// Serial.println("start of claw");
	// moveClaw(Direction::FORWARD);
	// delay(200);
	// moveClaw(Direction::REVERSE);
	// delay(200);
	// moveClaw(Direction::OFF);
	// delay(3000);
}
