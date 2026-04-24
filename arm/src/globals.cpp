#include "Constants.h"
#include "Arm.h"

// Instantiate global Dynamixel object
Dynamixel2Arduino dyna(DYNAMIXEL_MOTORS_SERIAL, -1);

bool solenoidEnabled = false;

// Set all of the externs to their initial values
#if (TESTING_LIMITS)
    bool Arm::isDisabled = false;
#else
    bool Arm::isDisabled = true;
#endif

uint32_t Arm::lastROSHeartbeatTime = 0;

// --- Multi-Turn Wrap Tracking (PM42-010-S260-R) ---
const int32_t WRIST_TICKS_PER_REV = 526374;
int32_t wrap_offset_M1 = 0;
int32_t wrap_offset_M2 = 0;
int32_t wrap_offset_M3 = 0;

// --- Calibration & Tracking Offsets ---
// Hardcode your mechanical zeros for the wrist here (if they are slightly off-center physically)
float dE_1 = 0.0;
float dE_2 = 0.0;
float dE_3 = 0.0;

// --- Dynamixel to Radian Coefficients ---
float k_bend = 3.14159265 / 526374.0;  // PM42 Resolution
float k_twst = 3.14159265 / 526374.0;
float k_grip = 0.00003933284;          // 13 threads per inch, for 1 inch, to go 90 deg

// --- Encoders & Angles ---
float enc1 = 0.0;
float enc2 = 0.0;
float enc3 = 0.0;

float bendAngle = 0.0;
float twstAngle = 0.0;
float gripAngle = 0.0;

// --- Targets ---
float targetM1 = 0.0;
float targetM2 = 0.0;
float targetM3 = 0.0;
float bendTarget = 0.0;
float twstTarget = 0.0;
float gripTarget = 0.0;


int32_t last_raw_M1 = 0;
int32_t last_raw_M2 = 0;