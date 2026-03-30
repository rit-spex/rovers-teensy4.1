#include "constants.h"
#include "science.h"
#include <Arduino.h>
#include <cmath>
#include <memory>


static std::shared_ptr<Science> science;
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
