#ifndef MAIN_H
#define MAIN_H

#include "constants.h"
#include "science.h"
#include <Arduino.h>
#include <cmath>
#include <memory>

static std::shared_ptr<Science> science;
static uint32_t prevMillis = millis();

void setup();
void loop();

#endif // MAIN_H
