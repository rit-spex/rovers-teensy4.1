#include "Constants.h"
#include "Arm.h"

Dynamixel2Arduino dyna(DYNAMIXEL_MOTORS_SERIAL, -1);

// set all of the externs to their initial values
if (TESTING_LIMITS)
{
    bool Arm::isDisabled = false;
}
else if
{
    bool Arm::isDisabled = true;
}

uint32_t Arm::lastROSHeartbeatTime = 0;

// arm movement stuff
float b_1 = 0.0;
float b_2 = 0.0;
float b_3 = 0.0;

float bend_offset = +00.0 * 3.14159265/180;
float twst_offset = +00.0 * 3.14159265/180;
float grip_offset = +00.0 * 3.14159265/180;

// Define tick-motor coefficients [rad/tick]
float k_bend =     3.14159265 / 526374;  // assuming (526,374 [tick] per 2π [rad]) except there are two motors so do half
float k_twst =     3.14159265 / 526374;
float k_grip = 52 * 2 * 3.14159265 / 4096;  // 13 threads per inch, for 1 inch, to go 90 deg

// Encoder positions
float enc1 = 0.0;
float enc2 = 0.0;
float enc3 = 0.0;

// Calculated angles
float bendAngle = 0.0;
float twstAngle = 0.0;
float gripAngle = 0.0;

// Targets
float targetM1 = 0.0;
float targetM2 = 0.0;
float targetM3 = 0.0;
float bendTarget = 0.0;
float twstTarget = 0.0;
float gripTarget = 0.0;
