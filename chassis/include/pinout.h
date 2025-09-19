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
#include "constants.h"

enum PINOUT
{
    CAN_RX_PIN = 0,
    CAN_TX_PIN = 1,
    MOTOR_PWM_PIN_1 = 2,
    MOTOR_PWM_PIN_2 = 3,
    MOTOR_PWM_PIN_3 = 4,
    MOTOR_PWM_PIN_4 = 5,
    MOTOR_PWM_PIN_5 = 6,
    MOTOR_PWM_PIN_6 = 7,
    ENC_A_PIN_1 = 8,
    ENC_B_PIN_1 = 9,

    // 10s
    ENC_A_PIN_2 = 10,
    ENC_B_PIN_2 = 11,
    ENC_A_PIN_3 = 12,
    STATUS_LIGHT_PIN = 13,
    EMPTY_14 = 14,
    ENC_B_PIN_6 = 15,
    ENC_A_PIN_6 = 16,
    ENC_B_PIN_5 = 17,
    EMPTY_18 = 18,
    EMPTY_19 = 19,

    // 20s
    ENC_A_PIN_5 = 20,
    ENC_B_PIN_4 = 21,
    ENC_A_PIN_4 = 22,
    ENC_B_PIN_3 = 23,
    THERMISTOR_PIN_0 = 24,
    THERMISTOR_PIN_1 = 25,
    THERMISTOR_PIN_2 = 26,
    THERMISTOR_PIN_3 = 27,
    EMPTY_28 = 28,
    EMPTY_29 = 29,

    // 30s
    EMPTY_30 = 30,
    EMPTY_31 = 31,
    EMPTY_32 = 32,
    EMPTY_33 = 33,
    EMPTY_34 = 34,
    EMPTY_35 = 35,
    EMPTY_36 = 36,
    EMPTY_37 = 37,
    EMPTY_38 = 38,
    EMPTY_39 = 39,

    // 40s
    EMPTY_40 = 40,
    EMPTY_41 = 41,
    EMPTY_42 = 42,
    EMPTY_43 = 43,
    EMPTY_44 = 44,
    EMPTY_45 = 45,
    EMPTY_46 = 46,
    EMPTY_47 = 47,
    EMPTY_48 = 48,
    EMPTY_49 = 49,

    // 50s
    FAN_PIN_0 = 50, // NOT VALID
    FAN_PIN_1 = 51, // NOT VALID
    FAN_PIN_2 = 52, // NOT VALID
    FAN_PIN_3 = 53, // NOT VALID
    EMPTY_54 = 54,
};

//********************************************************* DRIVETRAIN PINOUT **************************************************************************
// Wheel Number                                 1                         2                        3                       4                       5                       6
//******************************************************************************************************************************************************
#define MOTOR_PWM_PINS \
    (int[NUM_WHEELS]) { PINOUT::MOTOR_PWM_PIN_1, PINOUT::MOTOR_PWM_PIN_2, PINOUT::MOTOR_PWM_PIN_3, PINOUT::MOTOR_PWM_PIN_4, PINOUT::MOTOR_PWM_PIN_5, PINOUT::MOTOR_PWM_PIN_6 }
#define ENC_A_PINS \
    (int[NUM_WHEELS]) { PINOUT::ENC_A_PIN_1, PINOUT::ENC_A_PIN_2, PINOUT::ENC_A_PIN_3, PINOUT::ENC_A_PIN_4, PINOUT::ENC_A_PIN_5, PINOUT::ENC_A_PIN_6 }
#define ENC_B_PINS \
    (int[NUM_WHEELS]) { PINOUT::ENC_B_PIN_1, PINOUT::ENC_B_PIN_2, PINOUT::ENC_B_PIN_3, PINOUT::ENC_B_PIN_4, PINOUT::ENC_B_PIN_5, PINOUT::ENC_B_PIN_6 }

//********************************************************* TEMP PINOUT ********************************************************************************
// FAN Number                                            1                         2                         3                         4
//******************************************************************************************************************************************************
#define THERMISTOR_PINS \
    (int[NUM_THERMISTORS]) { PINOUT::THERMISTOR_PIN_0, PINOUT::THERMISTOR_PIN_1, PINOUT::THERMISTOR_PIN_2, PINOUT::THERMISTOR_PIN_3 }
#define FAN_PINS \
    (int[NUM_FANS]) { PINOUT::FAN_PIN_0, PINOUT::FAN_PIN_1, PINOUT::FAN_PIN_2, PINOUT::THERMISTOR_PIN_3 }

#endif
