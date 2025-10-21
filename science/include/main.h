#ifndef MAIN_H
#define MAIN_H

#include "constants.h"
#include "science.h"
#include <Arduino.h>
#include <cmath>
#include <memory>

static unsigned long currentRunCycle = 0;
static std::shared_ptr<Science> science;

void setup();
void loop();

#endif // MAIN_H
