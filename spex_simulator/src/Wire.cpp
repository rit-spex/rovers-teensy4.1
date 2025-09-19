// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : Wire.c
// purpose      : to simulate the wire file
// created on   : 7/23/2025 - Tyler
// last modified: 7/23/2025 - Tyler
// --------------------------------------------------------------------

#include <Wire.h>

void Wire_Class::begin()
{
    std::cout << "Wire begin called" << std::endl;
}
void Wire_Class::setSCL(int scl_pin)
{
    std::cout << "Wire setSCL called with pin: " << scl_pin << std::endl;
}
void Wire_Class::setSDA(int sda_pin)
{
    std::cout << "Wire setSDA called with pin: " << sda_pin << std::endl;
}
void Wire_Class::beginTransmission(int address)
{
    std::cout << "Wire beginTransmission called with address: " << address << std::endl;
}
void Wire_Class::write(int data)
{
    std::cout << "Wire write called with data: " << data << std::endl;
}
int  Wire_Class::read()
{
    std::cout << "Wire read called" << std::endl;
    return 0;
}
int  Wire_Class::read(int data)
{
    std::cout << "Wire read called with data: " << data << std::endl;
    return 0;
}
void Wire_Class::requestFrom(int device_num, int data)
{
    std::cout << "Wire requestFrom called with device_num: " << device_num;
    std::cout << " data: " << data << std::endl;
}
void Wire_Class::endTransmission()
{
    std::cout << "Wire endTransmission called" << std::endl;
}