// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : TimerOne.h
// purpose      : to simulate the main.h
// created on   : 8/6/2025 - Tyler
// last modified: 8/6/2025 - Tyler
// --------------------------------------------------------------------

#ifndef MAIN_H
#define MAIN_H

// Debugging
#define ENABLE_SERIAL 1
#define ARM_CAN

#include <Arduino.h>
#include <Dynamixel2Arduino.h>
#include <memory>

#include "Arm.h"
#include "CAN/CAN.h"
#include "Constants.h"
#include "Pinout.h"

void setup();
void loop();

#endif // MAIN_H
