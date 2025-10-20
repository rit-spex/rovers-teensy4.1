// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : Tic.c
// purpose      : to simulate the tic file
// created on   : 7/23/2025 - Tyler
// last modified: 7/23/2025 - Tyler
// --------------------------------------------------------------------

#include <Tic.h>

#include <spdlog/spdlog.h>

TicI2C::TicI2C()
{
    spdlog::debug("TicI2C constructor");
}

TicI2C::TicI2C(int address)
{
    spdlog::debug("TicI2C constructor called with address: {}", address);
}

void TicI2C::exitSafeStart()
{
    spdlog::debug("TicI2C exitSafeStart called");
}

void TicI2C::setTargetVelocity(int velocity)
{
    spdlog::debug("TicI2C setTargetVelocity called with velocity: {}", velocity);
}

void TicI2C::setTargetPosition(int pos)
{
    spdlog::debug("TicI2C setTargetPos called with pos: {}", pos);
}

void TicI2C::haltAndHold()
{
    spdlog::debug("TicI2C haltAndHold called");
}

void TicI2C::haltAndSetPosition(int pos)
{
    spdlog::debug("TicI2C haldAndSetPosition called with pos: {}", pos);
}

void TicI2C::resetCommandTimeout()
{
    spdlog::debug("TicI2C resetCommandTimeout called");
}
