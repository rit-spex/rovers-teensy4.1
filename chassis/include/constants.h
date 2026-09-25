// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : constants.h
// purpose      : This file contains all constants used in the system
// created on   : 8/14/2025 - Tyler
// last modified: 9/8/2025 - Tyler
// --------------------------------------------------------------------

#ifndef CONSTANTS_H
#define CONSTANTS_H

// #define LOG_LEVEL LOG_LEVEL_VERBOSE
#define LOG_LEVEL LOG_LEVEL_INFO
// #define LOG_LEVEL LOG_LEVEL_ERROR

//********************************************************* GENERAL CONSTANTS *******************************************************
// Update rate for the rover
#define HEARTBEAT_RATE_MS 100
#define STATUS_LIGHT_FREQUENCY_MS 200
#define TIMEOUT_DURAITON 2000 // ms

//********************************************************* DRIVETRAIN CONSTANTS *******************************************************
// The max percent of the motors
#define DRIVE_PERCENT_MAX 1.0

// the PMW values of the oDrive
#define MAX_DUTY_CYCLE (1500 + 500 * DRIVE_PERCENT_MAX)
#define NEUTRAL_DUTY_CYCLE 1500
#define MIN_DUTY_CYCLE (1500 - 500 * DRIVE_PERCENT_MAX)

// number of wheels on the rover
#define NUM_WHEELS 6

// The Direction of the motor
#define MOTOR_LEFT_SIGN -1 // positive 1 or negitive -1
#define MOTOR_RIGHT_SIGN -1 // positive 1 or negitive -1

#endif // CONSTANTS_H
