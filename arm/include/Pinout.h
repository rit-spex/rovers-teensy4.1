#ifndef PINOUT_H
#define PINOUT_H

// define the I2C pins for the arm
#define ARM_SDA_PIN 18
#define ARM_SCL_PIN 19

// define these pins, wristDir and shoulderDir can be any digital output
// wristSpeed and shoulderSpeed need to be pins 9 and 6
#define WRIST_DIR_PIN 33
#define WRIST_SPEED_PIN 6 // MUST BE PIN 6
#define SHOULDER_DIR_PIN 34
#define SHOULDER_SPEED_PIN 9 // MUST BE PIN 9

#endif
