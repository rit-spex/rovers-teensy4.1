#ifndef PINOUT_H
#define PINOUT_H

//********************************************************* ARM PINOUT
//*******************************************************
// define the I2C pins for the arm
#define ARM_SDA_PIN 18
#define ARM_SCL_PIN 19

// dir pins are also known as digital pins
// speed pins are also known as timer pins

// wrist is old
#define WRIST_DIR_PIN 33
#define WRIST_SPEED_PIN 6 // MUST BE PIN 6
#define SHOULDER_DIR_PIN 8
#define SHOULDER_SPEED_PIN 7
#define BASE_DIR_PIN 10
#define BASE_SPEED_PIN 9
#define ELBOW_DIR_PIN 5
#define ELBOW_SPEED_PIN 6
#define GRIPPER_PWM_PIN 37
#define SOLENOID_PIN 27
#define DYNAMIXEL_MOTORS_SERIAL Serial3
#define STATUS_LIGHT_PIN 13

#endif
