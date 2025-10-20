#include "main.h"

void setup()
{
    science = std::make_shared<Science>(&currentRunCycle);
    science->startUp();
    currentRunCycle = floor(millis() / UPDATE_RATE_MS);
}

void loop()
{
    science->runBackgroundProcesses();
    if (millis() >= UPDATE_RATE_MS * currentRunCycle) {
#if ENABLE_SERIAL
        // Serial.print("Current run cycle: ");
        // Serial.println((int)currentRunCycle);
#endif
        science->updateSubsystems();
        currentRunCycle++;
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
