// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : Dynamixel2Arduino.h
// purpose      : to simulate the Dynamixel2Arduino file
// created on   : 8/5/2025 - Tyler
// last modified: 8/5/2025 - Tyler
// --------------------------------------------------------------------

#ifndef DYNAMIXEL_2_ARDUNIO_H
#define DYNAMIXEL_2_ARDUNIO_H

#define UNIT_PERCENT 1
#define OP_PWM 1
#define Serial3 1

#include <stdio.h>

class Dynamixel2Arduino
{
public:
    Dynamixel2Arduino(int serial, int pin);
    void setGoalPWM(int pin, int speed, int unit);
    int setOperatingMode(int val1, int val2);
    int setPortProtocolVersion(int version);
    int setID(int oldID, int newID);
    void begin(int baudrate);
    int torqueOff(int pin);
    int torqueOn(int pin);
    int ping(int val);
    int ping();
};

#endif // DYNAMIXEL_2_ARDUNIO_H