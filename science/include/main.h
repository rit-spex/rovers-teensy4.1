#ifndef MAIN_H
#define MAIN_H

#include "science.h"
#include "constants.h"
#include <Arduino.h>
#include <memory>
#include <cmath>

static unsigned long currentRunCycle = 0;
static std::shared_ptr<Science> science;

void setup();
void loop();

#endif // MAIN_H
