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
#if ENABLE_SERIAL
	Serial.begin(9600);
	Serial.println("Arm");
	delay(1000);
#endif
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
			switch (i)
			{
			case 11:
				// sets func variable to the correct arm function based on the can message id thats new
				// func = &moveBase;
				moveBase(can->getUnpackedMessage((CAN::Message_ID)i, 1));
				break;
			case 12:
				// func = &moveShoulder;
				moveShoulder(can->getUnpackedMessage((CAN::Message_ID)i, 1));
				break;
			case 13:
				// func = &moveElbow;
				moveElbow(can->getUnpackedMessage((CAN::Message_ID)i, 1));
				break;
			case 14:
				// func = &bendWrist;
				bendWrist(dyna, can->getUnpackedMessage((CAN::Message_ID)i, 1));
				break;
			case 15:
				// func = &twistWrist;
				twistWrist(dyna, can->getUnpackedMessage((CAN::Message_ID)i, 1));
				break;
			case 16:
				// func = &moveClaw;
				moveClaw(dyna, can->getUnpackedMessage((CAN::Message_ID)i, 1));
				break;
			case 17:
				moveSolenoid(can->getUnpackedMessage((CAN::Message_ID)i, 1));
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
