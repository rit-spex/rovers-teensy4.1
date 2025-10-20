#ifndef MAIN
#define MAIN

// Debugging
#define ENABLE_SERIAL true

#include "science.h"
#include "constants.h"
#include <Arduino.h>
#include <memory>
#include <cmath>

static unsigned long currentRunCycle = 0;
static std::shared_ptr<Science> science;

void setup();
void loop();

#endif
