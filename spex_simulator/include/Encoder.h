// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : Encoder.h
// purpose      : to simulate the encoder file for chassis
// created on   : 8/13/2025 - Tyler
// last modified: 8/13/2025 - Tyler
// --------------------------------------------------------------------

#ifndef ENCODER_H
#define ENCODER_H

#include <iostream>

class Encoder
{
    private:
        int pin1;
        int pin2;
        int counts;
    public:
        Encoder(int pin1, int pin2);
        void attach(int pin1, int pin2);
        long read();
        void write(int value);
};

#endif //ENCODER_H