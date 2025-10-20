// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : Arduino.c
// purpose      : to simulate the arduino file
// created on   : 7/23/2025 - Tyler
// last modified: 7/23/2025 - Tyler
// --------------------------------------------------------------------

#include "PinState.h"
#include "Printer.h"
#include "spdlog/fmt/bundled/printf.h"
#include "spdlog/spdlog.h"
#include <Arduino.h>
#include <cerrno>
#include <cstdarg>

extern PinState pinState;

//////////////////////////////////////////// Serial_Class /////////////////////////
void Serial_Class::begin(int baudrate)
{
    spdlog::debug("Serial begin called with baudrate: {}", baudrate);
}
// print statements
void Serial_Class::print(const char *message)
{
    spdlog::debug("{}", message);
}
void Serial_Class::print(const int message)
{
    spdlog::debug("{}", message);
}
void Serial_Class::print(const float message)
{
    spdlog::debug("{}", message);
}

// println statements
void Serial_Class::println(const char *message)
{
    spdlog::debug(message);
}
void Serial_Class::println(const int message)
{
    spdlog::debug(message);
}
void Serial_Class::println(std::string message)
{
    spdlog::debug(message);
}

int Serial_Class::printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    // First, determine the size needed
    va_list args_copy;
    va_copy(args_copy, args);
    int size = vsnprintf(nullptr, 0, format, args_copy);
    va_end(args_copy);

    if (size < 0)
    {
        va_end(args);
        return size;
    }

    // Create buffer and format the string
    std::unique_ptr<char[]> buffer(new char[size + 1]);
    int result = vsnprintf(buffer.get(), size + 1, format, args);
    va_end(args);

    if (result < 0)
    {
        return result;
    }

    // Strip trailing newline
    std::string message(buffer.get());
    if (!message.empty() && message.back() == '\n')
    {
        message.pop_back();
    }

    // Log the formatted message
    spdlog::debug("{}", message);

    return result;
}

// define global functions
void pinMode(int pin, int mode)
{
    spdlog::debug("Pin {} mode set to {}", pin, (bool)mode ? "OUTPUT" : "INPUT");
    pinState.setPinMode(pin, mode);
}

void digitalWrite(int pin, int value)
{
    updateFile(PrinterData::PIN, pin, value);
    pinState.setPinValue(pin, value);
    // spdlog::debug("digitalWrite called with pin {} and value {}", pin, value);
}

int digitalRead(int pin)
{
    // spdlog::debug("digitalRead called with pin {}", pin);
    return pinState.getPinValue(pin);
}

void delay(int milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));

    spdlog::debug("Delay called with milliseconds: {}", milliseconds);
}

unsigned long millis()
{
    static std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    unsigned long time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    // spdlog::debug("Millis called at {}", time);
    return time;
}

void analogWrite(int pin, int pwm)
{
    updateFile(PrinterData::PIN, pin, pwm);
    pinState.setPinValue(pin, pwm);
    // spdlog::debug("analogWrite called with pin {} and pwm {}", pin, pwm);
}

float analogRead(int pin)
{
    // spdlog::debug("analogRead called");
    return pinState.getPinValue(pin);
}
