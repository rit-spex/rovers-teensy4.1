// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : Tic.c
// purpose      : to simulate the tic file
// created on   : 7/23/2025 - Tyler
// last modified: 7/23/2025 - Tyler
// --------------------------------------------------------------------

#include <Tic.h>

TicI2C::TicI2C()
{
    std::cout << "TicI2C constructor" << std::endl;
}
TicI2C::TicI2C(int address)
{
    std::cout << "TicI2C constructor called with address: " << address << std::endl;
}
void TicI2C::exitSafeStart()
{
    std::cout << "TicI2C exitSafeStart called" << std::endl;
}
void TicI2C::setTargetVelocity(int velocity)
{
    std::cout << "TicI2C setTargetVelocity called with velocity: " << velocity << std::endl;
}
void TicI2C::haltAndHold()
{
    std::cout << "TicI2C haltAndHold called" << std::endl;
}
void TicI2C::resetCommandTimeout()
{
    std::cout << "TicI2C resetCommandTimeout called" << std::endl;
}
