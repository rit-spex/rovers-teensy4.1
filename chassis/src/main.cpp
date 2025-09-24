// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : main.cpp
// purpose      : This the main file for the chassis.
//                This is the file arduino looks for main
// created on   : 8/14/2025 - Tyler
// last modified: 8/14/2025 - Tyler
// --------------------------------------------------------------------

#include "../include/main.h"

void setup()
{
    // *chassis = Chassis{&currentRunCycle};
    chassis = std::make_shared<Chassis>(&currentRunCycle);
    // start up the main body board, this will turn the status light off
    chassis->startUp();

#if ENABLE_SERIAL
    // this is the connection to the computer
    Serial.begin(9600);
    Serial.println("Chassis");
#endif

#if ENABLE_DEMO_ENCODER
    demo_encoder.begin();
#endif

    // update the currentRunCycle to be synced with the current time
    currentRunCycle = floor(millis() / UPDATE_RATE_MS);
}

void loop()
{
    chassis->runBackgroundProcess();
    if (millis() >= UPDATE_RATE_MS * currentRunCycle)
    {
#if ENABLE_SERIAL
        Serial.print("current cycle: ");
        Serial.println((int) currentRunCycle);

#if ENABLE_DEMO_ENCODER
        Serial.print("Demo Encoder RPM: ");
        Serial.println(demo_encoder.getRPM(millis() - UPDATE_RATE_MS * (currentRunCycle - 1)));
#endif
#endif // ENABLE_SERIAL

        unsigned long startTime = millis();

        // subtract the current cycle by one to get the entire timeframe

        // chassis->updateSubsystems(millis() - UPDATE_RATE_MS * (currentRunCycle - 1));
        chassis->updateSubsystems((currentRunCycle - 1));

#if ENABLE_SERIAL
        Serial.printf("time spent in loop: %d\n", millis() - startTime);
#endif

        // the increment to the next cycle
        currentRunCycle++;
    }
}
