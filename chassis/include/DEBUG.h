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

// enable when encoders are on the base
#define ENABLE_ENCODER   true

// enable to test with a single encoder
#define ENABLE_DEMO_ENCODER false

// enable each subsystem
#define ENABLE_CAN       false
#define ENABLE_DRIVEBASE true
#define ENABLE_TEMP      false
#define ENABLE_SERIAL    true

#define AUTO 0

// enables code that attempts to prevent the rover from tipping
#if AUTO
#define PREVENT_TIPPING 0
#else
#define PREVENT_TIPPING 1
#endif
