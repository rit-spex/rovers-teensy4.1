// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : main.h
// purpose      : This the header for the main program 
//                This is needed for the simulator to include main.cpp
// created on   : 8/14/2025 - Tyler
// last modified: 8/14/2025 - Tyler
// --------------------------------------------------------------------

#ifndef MAIN_H
#define MAIN_H

// System Includes
#include <Arduino.h>
#include <memory>

// Local Includes
#include "constants.h"
#include "DEBUG.h"
#include "chassis.h" // The drivebase is the chassis

#if ENABLE_DEMO_ENCODER
#include "quadDecoder.h"
#endif

#if ENABLE_DEMO_ENCODER
// #define ENCODER_RUN_CYCLE_MICROSEC 1000
// IntervalTimer encoderTimer;
static QuadratureDecoder demo_encoder{ENC_A_PIN_0, ENC_B_PIN_0};
#endif

// create the main body board
static unsigned long currentRunCycle = 0;
static std::shared_ptr<Chassis> chassis;

#endif //MAIN_H