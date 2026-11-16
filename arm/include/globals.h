#ifndef ARM_GLOBALS_H
#define ARM_GLOBALS_H

#include <Dynamixel2Arduino.h>
#include <cstdint>

// ---------------------------------------------------------------------------
// Runtime state shared between the arm translation units.
// Compile-time values (limits, unit conversions, motor properties) live in
// Constants.h.
// ---------------------------------------------------------------------------

// ---------------------- Hardware ----------------------
extern Dynamixel2Arduino dyna;

// ---------------------- Multi-turn wrap tracking ----------------------
// Set once a gearboxed potentiometer is used to measure the rotation number.
extern int32_t wrap_offset_M1;
extern int32_t wrap_offset_M2;
extern int32_t wrap_offset_M3;

extern int32_t last_raw_M1;
extern int32_t last_raw_M2;

// ---------------------- Zero/Homing offsets ----------------------
extern float dE_1;
extern float dE_2;
extern float dE_3;

// ---------------------- Encoder positions ----------------------
extern float enc1;
extern float enc2;
extern float enc3;

// ---------------------- Calculated angles ----------------------
extern float bendAngle;
extern float twstAngle;
extern float gripAngle;

// ---------------------- Targets ----------------------
extern float targetM1;
extern float targetM2;
extern float targetM3;
extern float bendTarget;
extern float twstTarget;
extern float gripTarget;

#endif // ARM_GLOBALS_H
