#include "TICT249.h"

#include <Arduino.h>

void delayWhileResettingCommandTimeout(uint32_t ms)
{
	uint32_t start = millis();
	do
	{
		tic.resetCommandTimeout();
	} while ((uint32_t)(millis() - start) <= ms);
}
