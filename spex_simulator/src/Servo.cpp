// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : Servo.h
// purpose      : to simulate the servo file
// created on   : 7/23/2025 - Tyler
// last modified: 7/23/2025 - Tyler
// --------------------------------------------------------------------

#include <Servo.h>

void Servo::attach(int pin, int min, int max)
{
    this->pin = pin;
    std::cout << "Servo attach called with pin: " << pin << " min: "<< min << " max: "<< max << std::endl;
}

void Servo::attach(int pin)
{
    this->pin = pin;
    std::cout << "Servo attach called with pin: " << pin << std::endl;
}


void Servo::detach()
{
    std::cout << "Servo detach called on pin: " << pin << std::endl;
}
void Servo::writeMicroseconds(int microseconds)
{
    std::cout << "Servo writeMicroseconds called with microseconds: " << microseconds << " on pin" << pin << std::endl;
}

void Servo::write(int microseconds)
{
    std::cout << "Servo write called with microseconds: " << microseconds << " on pin" << pin << std::endl;
}
