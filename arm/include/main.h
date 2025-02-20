#ifndef MAIN
#define MAIN

// Debugging
#define ENABLE_SERIAL true

#include <Arduino.h>
#include "Arm.h"
#include "CAN.h"

static Arm *arm;
static unsigned long currentRunCycle = 0;
static CAN *can;

#endif
