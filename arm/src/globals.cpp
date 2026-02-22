#include "globals.h"
#include "Constants.h"
#include "Pinout.h"
#include "Arm.h"

Dynamixel2Arduino dyna(DYNAMIXEL_MOTORS_SERIAL, FULL_DUPLEX_DIR_PIN);

// set all of the externs to their initial values
bool Arm::isDisabled = true;
uint32_t Arm::lastROSHeartbeatTime = 0;
float Arm::diff1PercentSpeed = DYNAMIXEL_SPEED_PERCENT;
float Arm::diff2PercentSpeed = DYNAMIXEL_SPEED_PERCENT;
float Arm::clawPercentSpeed = DYNAMIXEL_SPEED_PERCENT;
int Arm::gripperPos = MIN_GRIPPER_POS;