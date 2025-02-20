#ifndef MAIN
#define MAIN

// Debugging
#define ENABLE_SERIAL true

#include <Arduino.h>
#include "Arm.h"
#include "CAN.h"

Arm *arm;
unsigned long currentRunCycle = 0;
CAN *can;

#endif
