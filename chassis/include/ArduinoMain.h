#include "../include/Constants.h"
#include "../include/DEBUG.h"
#include "../include/Pinout.h"

// the simulator will emulate the hardware
#if ENABLE_SIMULATOR
#include "../TestSystem/Simulator.h"
#else
#include <Arduino.h>
#endif

// The drivebase is the main body board
#include "../include/MainBodyBoard.h"

// These allow the teensy to be the main controller
#if MASTER_TEENSY

// includes for the xbee
#if ENABLE_XBEE
#include "../include/Xbee.h"
#endif

// includes for the arm
#if ENABLE_ARM
#if ENABLE_SIMULATOR
#else
#include <Wire.h>
#endif // ENABLE_SIMULATOR
#include "../include/Arm.h"
#endif
#endif

void setup();
void loop();
