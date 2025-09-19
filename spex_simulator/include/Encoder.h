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

#include <Arduino.h>
#include <chrono>
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <thread>

// used to share data for the encoders
#if BUILD_CHASSIS
#include "pinout.h"
#endif

class Encoder
{
private:
    int pin1;
    int pin2;
    long counts;
    // pthread_t countIncreaseThread;
    unsigned long lastCountTime;

public:
    Encoder(int pin1, int pin2);
    void attach(int pin1, int pin2);
    long read();
    void write(int value);
};

#endif // ENCODER_H
