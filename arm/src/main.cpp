#include "main.h"

// void moveBase(int direction)
// {
// 	Serial.println("starting base");
// 	Serial.printf("direction: %d\n", direction);
// 	Serial.printf("duty_cycle: %d\n", FIFTY_PERCENT_DUTY_CYCLE);
// 	if (direction != 2)
// 	{
// 		// Serial.println("writing to pins");
// 		Serial.println("IM DOING TRICKS!!!!");
// 		digitalWrite(BASE_DIR_PIN, direction);
// 		Timer3.pwm(BASE_SPEED_PIN, FIFTY_PERCENT_DUTY_CYCLE);
// 	}
// 	else
// 	{
// 		Serial.println("stopping pins");
// 		Timer3.pwm(BASE_SPEED_PIN, 0);
// 	}
// }

// using namespace ControlTableItem;

Dynamixel2Arduino dyna(DYNAMIXEL_MOTORS_SERIAL, FULL_DUPLEX_DIR_PIN);

void setup()
{
#if ENABLE_SERIAL
	Serial.begin(9600);
	Serial.println("Arm");
	delay(1000);
#endif
	startUp(dyna);

	// startUpPos();
	// *can = CAN(&currentRunCycle);
	// can.startCAN();

	// Dynamixel2Arduino dyna(DYNAMIXEL_MOTORS_SERIAL, FULL_DUPLEX_DIR_PIN);
	// dyna.begin(DYNAMIXEL_BAUD_RATE);
	// Serial.printf("set protocol ver: %d\n", dyna.setPortProtocolVersion(DYNAMIXEL_PROTOCOL_VERSION));
	// Serial.printf("set torque off 1: %d\n", dyna.torqueOff(1));
	// Serial.printf("set torque off 2: %d\n", dyna.torqueOff(2));
	// delay(10);
	// Serial.printf("operating mode 1: %d\n", dyna.setOperatingMode(1, OP_PWM));
	// Serial.printf("operating mode 2: %d\n", dyna.setOperatingMode(2, OP_PWM));
	// delay(10);
	// Serial.printf("set torque on 1: %d\n", dyna.torqueOn(1));
	// Serial.printf("set torque on 2: %d\n", dyna.torqueOn(2));
	// delay(10);
	// dyna.ping();
	// delay(10);
	// Serial.printf("ping 1: %d\n", dyna.ping(1));
	// Serial.printf("ping 2: %d\n", dyna.ping(2));
	// delay(10);
	// Serial.begin(9600);
	// dyna.begin(57600);
	// Serial.printf("set port protocol %d\n", dyna.setPortProtocolVersion(2.0));
	// Serial.printf("set torque off 1 %d\n", dyna.torqueOff(1));
	// Serial.printf("set torque off 2 %d\n", dyna.torqueOff(2));
	// delay(10);
	// if (dyna.setOperatingMode(1, OP_PWM))
	// {
	// 	Serial.println("set operating mode");
	// };
	// if (dyna.setOperatingMode(2, OP_PWM))
	// {
	// 	Serial.println("set operating mode");
	// };
	// delay(10);
	// Serial.printf("set torque on 1 %d\n", dyna.torqueOn(1));
	// Serial.printf("set torque on 2 %d\n", dyna.torqueOn(2));
	// delay(10);

	// dyna.ping();
	// delay(10);

	// // if (dyna.writeControlTableItem(PROFILE_VELOCITY, 1, 0))
	// // {
	// // 	Serial.println("wrote to control table");
	// // }

	// printf("ping 1: %d\n", dyna.ping(1));
	// printf("ping 2: %d\n", dyna.ping(2));
}

void loop()
{
	Serial.println("turning on...");
	moveSolenoid(1);
	delay(1000);
	Serial.println("turning off...");
	moveSolenoid(0);
	delay(1000);
	return;
	// need to call this to read and "sniff" each message
	// 	can.readMsgBuffer();
	// 	if (can.isNewMessage(CAN::E_STOP))
	// 	{
	// 		arm.disable();
	// 	}
	// 	for (int i = 10; i < 16; ++i)
	// 	{
	// 		if (can.isNewMessage((CAN::Message_ID)i))
	// 		{
	// 			// declare arm specific function variable on the stack with param of Arm::Direction
	// 			void (Arm::*func)(Arm::Direction);
	// 			switch (i)
	// 			{
	// 			case 10:
	// 				// sets func variable to the correct arm function based on the can message id thats new
	// 				func = &Arm::moveBase;
	// 				break;
	// 			case 11:
	// 				func = &Arm::moveShoulder;
	// 				break;
	// 			case 12:
	// 				func = &Arm::moveElbow;
	// 				break;
	// 			case 13:
	// 				func = &Arm::bendWrist;
	// 				break;
	// 			case 14:
	// 				func = &Arm::twistWrist;
	// 				break;
	// 			case 15:
	// 				func = &Arm::moveClaw;
	// 				break;
	// 			default:
	// #if ENABLE_SERIAL
	// 				Serial.printf("message type not accounted for %d\n", i);
	// #endif
	// 				arm.disable();
	// 				break;
	// 			}
	// 			// if the message at index 0 is 1, then that part of the arm will stop
	// 			if(can.getUnpackedMessage((CAN::Message_ID)i,0)){
	// 				(arm.*func)(Arm::Direction::OFF);
	// 			} else {
	// 			// if the message at index 1 is 0, it will move in reverse, if the message is 1, then it will move forward
	// 				(arm.*func)(static_cast<Arm::Direction>(can.getUnpackedMessage((CAN::Message_ID)i,1)));
	// 			}
	// 		}
	// 	}

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
