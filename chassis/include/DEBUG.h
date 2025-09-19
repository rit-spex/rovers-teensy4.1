// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : DEBUG.h
// purpose      : This file is used to define the debug flags for the rover code.
//                If disable is defined, the corresponding subsystem will be disabled.
//                If debug is defined, the corresponding subsystem will be serial printed
// created on   : 3/21/2024 - Tyler
// last modified: 8/14/2025 - Tyler
// --------------------------------------------------------------------

#ifndef DEBUG_H
#define DEBUG_H

// enable when encoders are on the base
#define ENABLE_ENCODER false

// enable to test with a single encoder
#define ENABLE_DEMO_ENCODER false

// toggle the motors ramp, manually turn off when using PID
#define ENABLE_MOTOR_RAMP true

// enable each subsystem
#define ENABLE_CAN true
#define ENABLE_DRIVEBASE true
#define ENABLE_TEMP true
#define ENABLE_SERIAL false

#define AUTO 0

// enables code that attempts to prevent the rover from tipping
#if AUTO
#define PREVENT_TIPPING 0
#else
#define PREVENT_TIPPING 1
#endif

#endif