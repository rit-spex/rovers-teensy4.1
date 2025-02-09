#include "TICT249.h"

void setup()
{
	// Set up I2C.
	Wire.begin();

	// Give the Tic some time to start up.
	delay(20);

	// Tells the Tic that it is OK to start driving the motor.  The
	// Tic's safe-start feature helps avoid unexpected, accidental
	// movement of the motor: if an error happens, the Tic will not
	// drive the motor again until it receives the Exit Safe Start
	// command.  The safe-start feature can be disbled in the Tic
	// Control Center.
	tic.exitSafeStart();
}

void loop()
{
	// Move forward at 200 steps per second for 2 seconds.
	tic.setTargetVelocity(2000000);
	delayWhileResettingCommandTimeout(2000);
}
