#ifndef CONSTANTS_H
#define CONSTANTS_H

// I2C device number for ARM
#define BASE_I2C_ID 15 // brushed motor
#define BASE_MAX_SPEED 800
#define FIFTY_PERCENT_DUTY_CYCLE 511

#define DYNAMIXEL_PROTOCOL_VERSION 2.0
#define DYNAMIXEL_BAUD_RATE 57600
#define DYNAMIXEL_SPEED_PERCENT                                                                    \
    100.0 // lets the D2A library know that we don't have a shield for the arduino also isn't actually a pinout so thats why its in here
#define FULL_DUPLEX_DIR_PIN (-1)

#define MAX_GRIPPER_POS 110
#define MIN_GRIPPER_POS 90
#define GRIPPER_SPEED 1

#define TIME 80

#define LED_BLINK_INTERVAL 500 // ms

// Old definitions:
// #define CLAW_I2C_ID 16 // stepper motor
// #define CLAW_MAX_SPEED (200 * 10000) // 100 steps per second

#endif // CONSTANTS_H
