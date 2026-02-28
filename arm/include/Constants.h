#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Dynamixel2Arduino.h>


#define ENABLE_SERIAL 1
#define TESTING_LIMITS 0

// ---------------------- Dynamixel ----------------------
#define DYNAMIXEL_PROTOCOL_VERSION 1.0
#define DYNAMIXEL_BAUD_RATE 57600
#define DYNAMIXEL_MOTORS_SERIAL Serial4      // hardware UART for Dynamixels


// ---------------------- Timing ----------------------
#define LED_BLINK_INTERVAL 500  // milliseconds
#define TIMEOUT_DURAITON 2000 // ms

// ---------------------- Pinout ----------------------

// #define FULL_DUPLEX_DIR_PIN 2         // GPIO controlling half/full duplex TX/RX
#define LIMIT_SWITCH_PIN 5
#define SOLENOID_PIN 29
#define STATUS_LIGHT_PIN 13     // This is on the Teensy, not an ACTUAL pin

// ---------------------- Globals ----------------------
extern Dynamixel2Arduino dyna;
extern bool solenoidEnabled;

// Spin offsets
extern float b_1;
extern float b_2;
extern float b_3;
extern float bend_offset;
extern float twst_offset;
extern float grip_offset;

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


#endif // CONSTANTS_H
