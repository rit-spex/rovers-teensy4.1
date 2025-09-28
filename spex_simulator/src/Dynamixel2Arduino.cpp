// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : Dynamixel2Arduino.cpp
// purpose      : to simulate the Dynamixel2Arduino file
// created on   : 8/6/2025 - Tyler
// last modified: 8/6/2025 - Tyler
// --------------------------------------------------------------------

#include "Dynamixel2Arduino.h"

Dynamixel2Arduino::Dynamixel2Arduino(int serial, int pin)
{
    printf("Dynamixel2Arduino constructor serial: %d, pin %d\n", serial, pin);
}

void Dynamixel2Arduino::setGoalPWM(int pin, int speed, int unit)
{
    printf("Dynamixel2Arduino setGoalPWM: pin: %d, speed %d, unit %d\n", pin, speed, unit);
}

int Dynamixel2Arduino::setOperatingMode(int val1, int val2)
{
    printf("Dynamixel2Arduino setOperatingMode val1: %d, val2: %d\n", val1, val2);

    return 1;
}

int Dynamixel2Arduino::setPortProtocolVersion(int version)
{
    printf("Dynamixel2Arduino setPortProtocolVersion version: %d\n", version);

    return 1;
}

int Dynamixel2Arduino::setID(int oldID, int newID)
{
    printf("Dynamixel2Arduino setID oldID: %d, newID: %d\n", oldID, newID);

    return 1;
}

void Dynamixel2Arduino::begin(int baudrate)
{
    printf("Dynamixel2Arduino begin baudrate: %d\n", baudrate);
}

int Dynamixel2Arduino::torqueOff(int pin)
{
    printf("Dynamixel2Arduino torqueOff pin: %d\n", pin);

    return 1;
}

int Dynamixel2Arduino::torqueOn(int pin)
{
    printf("Dynamixel2Arduino torqueOn pin: %d\n", pin);

    return 1;
}

int Dynamixel2Arduino::ping(int val)
{
    printf("Dynamixel2Arduino ping val:%d\n", val);

    return 1;
}

int Dynamixel2Arduino::ping()
{
    printf("Dynamixel2Arduino ping\n");

    return 1;
}
