#include "main.h"

static uint32_t prevMillis = millis();

void setup()
{
    science = std::make_shared<Science>();
    science->startUp();
}

void loop()
{
    science->runBackgroundProcesses();
    if (uint32_t currMillis = millis(); currMillis - prevMillis >= UPDATE_RATE_MS)
    {
        prevMillis = currMillis;
        science->updateSubsystems();
    }
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
