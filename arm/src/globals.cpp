#include "globals.h"
#include "Constants.h"
#include "Pinout.h"

#define ENABLE_SERIAL 1

Dynamixel2Arduino dyna(DYNAMIXEL_MOTORS_SERIAL, FULL_DUPLEX_DIR_PIN);
