// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : Arduino.h
// purpose      : to simulate the arduino file
// created on   : 7/23/2025 - Tyler
// last modified: 7/23/2025 - Tyler
// --------------------------------------------------------------------

#ifndef ARDUINO_H
#define ARDUINO_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <thread>
#include <unordered_map>

#define LOW 0
#define HIGH 1

#define INPUT_PULLUP 1
#define INPUT_PULLDOWN 0

#define INPUT 0
#define OUTPUT 1

class Serial_Class
{
public:
    void begin(int baudrate);

    // print statements
    void print(const char *message);
    void print(const int message);
    void print(const float message);

    // println statements
    void println(const char *message);
    void println(const int message);
    void println(std::string message);
    void println();

    // printf
    int printf(const char *format, ...);
};

// define global functions
void pinMode(int pin, int mode);
void delay(int milliseconds);
unsigned long millis();

void digitalWrite(int pin, int value);
int digitalRead(int pin);

void analogWrite(int pin, int pwm);
float analogRead(int pin);

static Serial_Class Serial;

#endif
