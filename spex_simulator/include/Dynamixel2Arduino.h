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
// #define Serial4 1
#define Serial3 1
#define Serial2 1

#include <Arduino.h>
#include <stdio.h>

enum OperatingMode{
    OP_CURRENT = 0,
    OP_VELOCITY = 1,
    OP_POSITION = 3,
    OP_EXTENDED_POSITION = 4,
    OP_CURRENT_BASED_POSITION = 5,
    OP_PWM = 16,
};

class Dynamixel2Arduino
{
public:
    Dynamixel2Arduino(Serial_Class serial, int pin);
    void setGoalPWM(int pin, int speed, int unit);
    bool setGoalPosition(int id, float value);
    float getPresentPosition(int id);
    int setOperatingMode(int val1, int val2);
    int setPortProtocolVersion(int version);
    int setID(int oldID, int newID);
    void begin(int baudrate);
    void begin();
    int torqueOff(int pin);
    int torqueOn(int pin);
    int ping(int val);
    int ping();

private:
    float presentPosition[3] = {0.0};
};

#endif // DYNAMIXEL_2_ARDUNIO_H
