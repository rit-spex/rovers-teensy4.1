#include "SMC.h"

void setup()
{
    Wire.begin();
    exitSafeStart();
}

void loop()
{
    // Read the up time from the controller and send it to
    // the serial monitor.
    uint16_t upTime = readUpTime();
    Serial.print(F("Up time: "));
    Serial.println(upTime);
    setMotorSpeed(3200); // full-speed forward
    delay(50);
}
