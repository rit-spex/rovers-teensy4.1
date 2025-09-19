// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : Servo.h
// purpose      : to simulate the servo file
// created on   : 7/23/2025 - Tyler
// last modified: 7/23/2025 - Tyler
// --------------------------------------------------------------------

#ifndef SERVO_H
#define SERVO_H

#include <iostream>
#include "Printer.h"

// used to share data for the encoders
#if BUILD_CHASSIS
#include "pinout.h"
#endif

class Servo
{
private:
    int pin;

public:
    void attach(int pin);
    void attach(int pin, int min, int max);
    void detach();
    void writeMicroseconds(int microseconds);
    void write(int microseconds);
};

#endif