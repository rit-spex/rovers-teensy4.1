#include "main.h"

void setup()
{
	*can = CAN(&currentRunCycle);
	can->startCAN();
}

void loop()
{
	if (can->isNewMessage(CAN::E_STOP))
	{

	}
	for (int i = 20; i < 22; ++i)
	{
		if (can->isNewMessage((CAN::Message_ID)i))
		{
			switch (i)
			{
			case 20:
				break;
			case 21:
				break;
			default:
				Serial.printf("message type not accounted for %d\n", i);
				break;
			}
		}
	}
}
