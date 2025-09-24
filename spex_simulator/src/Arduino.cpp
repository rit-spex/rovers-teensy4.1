// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : Arduino.c
// purpose      : to simulate the arduino file
// created on   : 7/23/2025 - Tyler
// last modified: 7/23/2025 - Tyler
// --------------------------------------------------------------------

#include "Printer.h"
#include <Arduino.h>
#include <cerrno>
#include <cstdarg>

int PinState::getPinValue(const int pin)
{
    return m_pinMap[pin];
}

void PinState::setPinValue(const int pin, const int val)
{
    m_pinMap[pin] = val;
}

//////////////////////////////////////////// Serial_Class /////////////////////////
void Serial_Class::begin(int baudrate)
{
    std::cout << "Serial begin called with baudrate: " << baudrate << std::endl;
}
// print statements
void Serial_Class::print(const char *message)
{
    std::cout << message;
}
void Serial_Class::print(const int message)
{
    std::cout << message;
}
void Serial_Class::print(const float message)
{
    std::cout << message;
}

// println statements
void Serial_Class::println(const char *message)
{
    std::cout << message << std::endl;
}
void Serial_Class::println(const int message)
{
    std::cout << message << std::endl;
}
void Serial_Class::println(std::string message)
{
    std::cout << "Serial println called with message: " << message << std::endl;
}

int Serial_Class::printf(const char *format, ...)
{
    va_list args;
    int done;

    va_start(args, format);
    done = vfprintf(stdout, format, args);
    va_end(args);

    return done;
}

// define global functions
void pinMode(int pin, int mode)
{
    std::cout << "pinMode called with pin: " << pin << " and mode: " << mode << std::endl;
}

void digitalWrite(int pin, int value)
{
    updateFile(PrinterData::PIN, pin, value);
    pinState.setPinValue(pin, value);
    // std::cout << "digitalWrite called with pin: " << pin << " and value: " << value << std::endl;
}

int digitalRead(int pin)
{
    std::cout << "digitalRead called with pin: " << pin << std::endl;
    return pinState.getPinValue(pin);
}

void delay(int milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));

    std::cout << "delay called with milliseconds: " << milliseconds << std::endl;
}

unsigned long millis()
{
    static std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    unsigned long time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    // std::cout << "millis called at " << time << std::endl;
    return time;
}

void analogWrite(int pin, int pwm)
{
    updateFile(PrinterData::PIN, pin, pwm);
    pinState.setPinValue(pin, pwm);
    // std::cout << "analogWrite called" << std::endl;
}

float analogRead(int pin)
{
    std::cout << "analogRead called" << std::endl;
    return pinState.getPinValue(pin);
}

// XXX: SUPER MESSY WAY TO HANDLE GLOBAL SHARED STATE
PinState *getPinStatePtr()
{
    return &pinState;
}
