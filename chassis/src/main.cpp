#include "../include/main.h"

void setup()
{
	// *mbb = MainBodyBoard{&currentRunCycle};
	mbb = std::make_shared<MainBodyBoard>(&currentRunCycle);
	//   start up the main body board, this will turn the status light off
	mbb->startUp();

#if ENABLE_SERIAL
	// this is the connection to the computer
	Serial.begin(9600);
	Serial.println("Main Body Board");
#endif

#if ENABLE_DEMO_ENCODER
	demo_encoder.begin();
#endif

	// update the currentRunCycle to be synced with the current time
	currentRunCycle = floor(millis() / UPDATE_RATE_MS);
}

void loop()
{
	mbb->runBackgroundProcess();
	if (millis() >= UPDATE_RATE_MS * currentRunCycle)
	{
#if ENABLE_SERIAL
		Serial.print("current cycle: ");
		Serial.println((int)currentRunCycle);

#if ENABLE_DEMO_ENCODER
		Serial.println(demo_encoder.getRPM(millis() - UPDATE_RATE_MS * (currentRunCycle - 1)));
#endif
#endif // ENABLE_SERIAL

		// subtract the current cycle by one to get the entire timeframe
		mbb->updateSubsystems(millis() - UPDATE_RATE_MS * (currentRunCycle - 1));

		// the increment to the next cycle
		currentRunCycle++;
	}
}
