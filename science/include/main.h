#ifndef MAIN
#define MAIN

// Debugging
#define ENABLE_SERIAL

#include "CAN.h"
#include "Science.h"
#include <Arduino.h>

static unsigned long currentRunCycle = 0;
static CAN *can;

void setup();
void loop();

#endif
