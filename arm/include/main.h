#ifndef MAIN
#define MAIN

#include "Arm.h"
#include "CAN.h"

Arm arm;
CAN can;
unsigned long currentRunCycle = 0;

void setup();
void loop();

#endif
