#include <Dynamixel2Arduino.h>

// ---------------------- Globals (Externs) ----------------------
extern Dynamixel2Arduino dyna;
extern bool solenoidEnabled;

// Motor Properties
extern const int32_t WRIST_TICKS_PER_REV;

// Multi-Turn Wrap Tracking
extern int32_t wrap_offset_M1;
extern int32_t wrap_offset_M2;
extern int32_t wrap_offset_M3;


extern int32_t last_raw_M1;
extern int32_t last_raw_M2;

// Zero/Homing offsets
extern float dE_1;
extern float dE_2;
extern float dE_3;

// Tick-motor coefficients
extern float k_bend;
extern float k_twst;
extern float k_grip;

// Encoder positions
extern float enc1;
extern float enc2;
extern float enc3;

// Calculated angles
extern float bendAngle;
extern float twstAngle;
extern float gripAngle;

// Targets
extern float targetM1;
extern float targetM2;
extern float targetM3;
extern float bendTarget;
extern float twstTarget;
extern float gripTarget;