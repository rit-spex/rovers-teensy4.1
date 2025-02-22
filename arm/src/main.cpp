#include "main.h"

Arm arm{};
currentRunCycle = 0;
CAN can{&currentRunCycle};

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
	if (can->isNewMessage(CAN::E_STOP))
	{
		arm->disable();
	}
	for (int i = 10; i < 16; ++i)
	{
		if (can->isNewMessage((CAN::Message_ID)i))
		{
			switch (i)
			{
			case 10:
				break;
			case 11:
				break;
			case 12:
				break;
			case 13:
				break;
			case 14:
				break;
			case 15:
				break;
			default:
#if ENABLE_SERIAL
				Serial.printf("message type not accounted for %d\n", i);
#endif
				arm->disable();
				break;
			}
		}
	}
}
