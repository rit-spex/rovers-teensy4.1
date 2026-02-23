#include "Constants.h"
#include "Arm.h"

Dynamixel2Arduino dyna(DYNAMIXEL_MOTORS_SERIAL, FULL_DUPLEX_DIR_PIN);

// set all of the externs to their initial values
bool Arm::isDisabled = true;
uint32_t Arm::lastROSHeartbeatTime = 0;