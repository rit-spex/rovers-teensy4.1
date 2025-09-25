// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : Dynamixel2Arduino.cpp
// purpose      : to simulate the Dynamixel2Arduino file
// created on   : 8/6/2025 - Tyler
// last modified: 8/6/2025 - Tyler
// --------------------------------------------------------------------

#include "Dynamixel2Arduino.h"
#include "spdlog/spdlog.h"

Dynamixel2Arduino::Dynamixel2Arduino(int serial, int pin)
{
    spdlog::debug("Dynamixel2Arduino constructor serial {}, pin {}", serial, pin);
}

void Dynamixel2Arduino::setGoalPWM(int pin, int speed, int unit)
{
    spdlog::debug("Dynamixel2Arduino setGoalPWM: pin {}, speed {}, unit {}", pin, speed, unit);
}

int Dynamixel2Arduino::setOperatingMode(int val1, int val2)
{
    spdlog::debug("Dynamixel2Arduino setOperatingMode val1: {}, val2: {}", val1, val2);

    return 1;
}

int Dynamixel2Arduino::setPortProtocolVersion(int version)
{
    spdlog::debug("Dynamixel2Arduino setPortProtocolVersion version: {}", version);

    return 1;
}

int Dynamixel2Arduino::setID(int oldID, int newID)
{
    spdlog::debug("Dynamixel2Arduino setID oldID: {}, newID: {}", oldID, newID);

    return 1;
}

void Dynamixel2Arduino::begin(int baudrate)
{
    spdlog::debug("Dynamixel2Arduino begin baudrate: {}", baudrate);
}

int Dynamixel2Arduino::torqueOff(int pin)
{
    spdlog::debug("Dynamixel2Arduino torqueOff pin: {}", pin);

    return 1;
}

int Dynamixel2Arduino::torqueOn(int pin)
{
    spdlog::debug("Dynamixel2Arduino torqueOn pin: {}", pin);

    return 1;
}

int Dynamixel2Arduino::ping(int val)
{
    spdlog::debug("Dynamixel2Arduino ping val: {}", val);

    return 1;
}

int Dynamixel2Arduino::ping()
{
    spdlog::debug("Dynamixel2Arduino ping");

    return 1;
}
