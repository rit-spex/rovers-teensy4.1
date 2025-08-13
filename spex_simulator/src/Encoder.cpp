// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : Encoder.cpp
// purpose      : to simulate the encoder file for chassis
// created on   : 8/13/2025 - Tyler
// last modified: 8/13/2025 - Tyler
// --------------------------------------------------------------------

#include <Encoder.h>

Encoder::Encoder(int pin1, int pin2)
{
    this->pin1 = pin1;
    this->pin2 = pin2;
    this->counts = 1000;
    std::cout << "Encoder constructor called" << std::endl;
}
void Encoder::attach(int pin1, int pin2)
{
    this->pin1 = pin1;
    this->pin2 = pin2;
    std::cout << "Encoder attach called with pin1: " << pin1 << " and pin2: " << pin2 << std::endl;
}
long Encoder::read()
{
    //std::cout << "Encoder read called on encoder with pins: "<< pin1 << ", " << pin2 << std::endl;
    return this->counts;
}
void Encoder::write(int value)
{
    //std::cout << "Encoder write called with value: " << value << std::endl;
}