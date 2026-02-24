#include "Constants.h"
#include "Arm.h"

Dynamixel2Arduino dyna(DYNAMIXEL_MOTORS_SERIAL, FULL_DUPLEX_DIR_PIN);

// set all of the externs to their initial values
bool Arm::isDisabled = true;
uint32_t Arm::lastROSHeartbeatTime = 0;

// arm movement stuff
float b_1 = 0.0;
float b_2 = 0.0;
float b_3 = 0.0;

// Define tick-motor coefficients
float k_bend = 2 * 3.14159265 / 4096;  // assuming 4096 counts = 2*pi radians
float k_twst = 2 * 3.14159265 / 4096;
float k_grip = 2 * 3.14159265 / 4096;

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
