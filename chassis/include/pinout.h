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
    EMPTY_8 = 8,
    EMPTY_9 = 9,

    // 10s
    EMPTY_10 = 10,
    EMPTY_11 = 11,
    EMPTY_12 = 12,
    STATUS_LIGHT_PIN = 13,
    EMPTY_14 = 14,
    EMPTY_15 = 15,
    EMPTY_16 = 16,
    EMPTY_17 = 17,
    EMPTY_18 = 18,
    EMPTY_19 = 19,

    // 20s
    EMPTY_20 = 20,
    EMPTY_21 = 21,
    EMPTY_22 = 22,
    EMPTY_23 = 23,
    EMPTY_24 = 24,
    EMPTY_25 = 25,
    EMPTY_26 = 26,
    EMPTY_27 = 27,
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
    EMPTY_50 = 50,
    EMPTY_51 = 51,
    EMPTY_52 = 52,
    EMPTY_53 = 53,
    EMPTY_54 = 54,
};

//********************************************************* DRIVETRAIN PINOUT **************************************************************************
// Wheel Number                                 1                         2                        3                       4                       5                       6
//******************************************************************************************************************************************************
#define MOTOR_PWM_PINS (int[NUM_WHEELS]){PINOUT::MOTOR_PWM_PIN_1, PINOUT::MOTOR_PWM_PIN_2, PINOUT::MOTOR_PWM_PIN_3, PINOUT::MOTOR_PWM_PIN_4, PINOUT::MOTOR_PWM_PIN_5, PINOUT::MOTOR_PWM_PIN_6}

#endif // PINOUT_H
