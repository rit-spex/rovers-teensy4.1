// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : Wire.h
// purpose      : to simulate the wire file
// created on   : 7/23/2025 - Tyler
// last modified: 7/23/2025 - Tyler
// --------------------------------------------------------------------

#ifndef WIRE_H
#define WIRE_H

#include <cstdint>
#include <iostream>

class Wire_Class
{
public:
    void begin();
    void setSCL(int scl_pin);
    void setSDA(int sda_pin);
    void beginTransmission(int address);
    void write(int data);
    int read();
    int read(int data);
    void requestFrom(int device_num, int data);
    void endTransmission();
};

static Wire_Class Wire;

#endif
