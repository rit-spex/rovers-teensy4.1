#include "main.h"

void setup()
{
#if ENABLE_SERIAL
	Serial.begin(9600);
	Serial.println("Arm");
#endif
	*arm = Arm();
	arm->startUp();
	*can = CAN(&currentRunCycle);
	can->startCAN();
}

void loop()
{
	// need to call this to read and "sniff" each message
	can->readMsgBuffer();
	if (can->isNewMessage(CAN::E_STOP))
	{
		arm->disable();
	}
	for (int i = 10; i < 16; ++i)
	{
		if (can->isNewMessage((CAN::Message_ID)i))
		{
			// declare arm specific function variable on the stack with param of Arm::Direction
			void (Arm::*func)(Arm::Direction); 
			switch (i)
			{
			case 10:
				// sets func variable to the correct arm function based on the can message id thats new
				func = &Arm::moveBase;
				break;
			case 11:
				func = &Arm::moveShoulder;
				break;
			case 12:
				func = &Arm::moveElbow;
				break;
			case 13:
				func = &Arm::bendWrist;
				break;
			case 14:
				func = &Arm::twistWrist;
				break;
			case 15:
				func = &Arm::moveClaw;
				break;
			default:
#if ENABLE_SERIAL
				Serial.printf("message type not accounted for %d\n", i);
#endif
				arm->disable();
				break;
			}
			// if the message at index 0 is 1, then that part of the arm will stop
			if(can->getUnpackedMessage((CAN::Message_ID)i,0)){
				(arm->*func)(Arm::Direction::OFF);
			} else {
			// if the message at index 1 is 0, it will move in reverse, if the message is 1, then it will move forward
				(arm->*func)(static_cast<Arm::Direction>(can->getUnpackedMessage((CAN::Message_ID)i,1)));
			}
		}
	}

	/* Test */
	// arm->moveBase(Arm::Direction::FORWARD);
	// delay(100);
	// arm->moveBase(Arm::Direction::REVERSE);
	// delay(100);
	// arm->moveBase(Arm::Direction::OFF);
	// delay(3000);
	// arm->moveShoulder(Arm::Direction::FORWARD);
	// delay(100);
	// arm->moveShoulder(Arm::Direction::REVERSE);
	// delay(100);
	// arm->moveShoulder(Arm::Direction::OFF);
	// delay(3000);
	// arm->moveElbow(Arm::Direction::FORWARD);
	// delay(100);
	// arm->moveElbow(Arm::Direction::REVERSE);
	// delay(100);
	// arm->moveElbow(Arm::Direction::OFF);
	// delay(3000);
	// arm->twistWrist(Arm::Direction::FORWARD);
	// delay(100);
	// arm->twistWrist(Arm::Direction::REVERSE);
	// delay(100);
	// arm->twistWrist(Arm::Direction::OFF);
	// delay(3000);
	// arm->bendWrist(Arm::Direction::FORWARD);
	// delay(100);
	// arm->bendWrist(Arm::Direction::REVERSE);
	// delay(100);
	// arm->bendWrist(Arm::Direction::OFF);
	// delay(3000);
	// arm->moveClaw(Arm::Direction::FORWARD);
	// delay(100);
	// arm->moveClaw(Arm::Direction::REVERSE);
	// delay(100);
	// arm->moveClaw(Arm::Direction::OFF);
	// delay(3000);
}
