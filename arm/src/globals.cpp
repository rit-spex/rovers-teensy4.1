#include "Constants.h"
#include "globals.h"

#include "Arm.h"

// Instantiate global Dynamixel object
Dynamixel2Arduino dyna(DYNAMIXEL_MOTORS_SERIAL, -1);

// Set all of the externs to their initial values
#if (TESTING_LIMITS)
    bool Arm::isDisabled = false;
#else
    bool Arm::isDisabled = true;
#endif

bool Arm::isEStopped = false;

uint32_t Arm::lastROSHeartbeatTime = 0;

// Gripper command watchdog state
unsigned long Arm::lastGripperCmdTime = 0;
bool Arm::gripperCmdPending = false;

// Time of the last latched e-stop, used to rate-limit clearing it
unsigned long Arm::lastEStopTime = 0;

// ---------------------- Multi-Turn Wrap Tracking (PM42-010-S260-R) ----------------------
// TODO: These offsets are no longer read from or written to battery-backed RAM.
// A future implementation will use a gearboxed potentiometer to read the current
// rotation number and offset the motor ticks accordingly.
int32_t wrap_offset_M1 = 0;
int32_t wrap_offset_M2 = 0;

// ---------------------- Calibration & Tracking Offsets ----------------------
// Hardcode your mechanical zeros for the wrist here (if they are slightly off-center physically)
float dE_1 = 0.0;
float dE_2 = 0.0;
float dE_3 = 0.0;

// ---------------------- Encoders & Angles ----------------------
float enc1 = 0.0;
float enc2 = 0.0;
float enc3 = 0.0;

float bendAngle = 0.0;
float twstAngle = 0.0;
float gripAngle = 0.0;

// ---------------------- Targets ----------------------
float targetM1 = 0.0;
float targetM2 = 0.0;
float targetM3 = 0.0;
float bendTarget = 0.0;
float twstTarget = 0.0;
float gripTarget = 0.0;

int32_t last_raw_M1 = 0;
int32_t last_raw_M2 = 0;
