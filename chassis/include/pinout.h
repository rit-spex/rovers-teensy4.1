// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : pinout.h
// purpose      : This file contains all of the pin slots used in the system
// created on   : 8/14/2025 - Tyler
// last modified: 8/14/2025 - Tyler
// --------------------------------------------------------------------

#ifndef PINOUT_H
#define PINOUT_H

//********************************************************* GENERAL PINOUT *******************************************************
#define STATUS_LIGHT_PIN 13

//********************************************************* DRIVETRAIN PINOUT ****************************************************

enum PWM_PINS 
{
    PWM_PIN_0 = 2,
    PWM_PIN_1 = 3,
    PWM_PIN_2 = 4,
    PWM_PIN_3 = 5, // is 12 on proto-board
    PWM_PIN_4 = 6, // is 10 on proto-board
    PWM_PIN_5 = 7  // is 11 on proto-board
};

enum ENC_A_PINS 
{
    ENC_A_PIN_0 = 8, // is 31 on proto-board
    ENC_A_PIN_1 = 10,
    ENC_A_PIN_2 = 12,
    ENC_A_PIN_3 = 22,
    ENC_A_PIN_4 = 20,
    ENC_A_PIN_5 = 16 
};

enum ENC_B_PINS 
{
    ENC_B_PIN_0 = 9, // is 30 on proto-board
    ENC_B_PIN_1 = 11,
    ENC_B_PIN_2 = 23,
    ENC_B_PIN_3 = 21,
    ENC_B_PIN_4 = 17,
    ENC_B_PIN_5 = 15
};

//********************************************************* TEMP PINOUT *******************************************************

enum THERMISTOR_PINS 
{
    THERMISTOR_PIN_0 = 24,
    THERMISTOR_PIN_1 = 25,
    THERMISTOR_PIN_2 = 26,
    THERMISTOR_PIN_3 = 27
};

enum FAN_PINS 
{
    FAN_PIN_0 = 28, // not valid
    FAN_PIN_1 = 23, // not valid
    FAN_PIN_2 = 24, // not valid
    FAN_PIN_3 = 25  // not valid
};

#endif
