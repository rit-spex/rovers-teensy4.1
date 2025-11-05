// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : Tic.h
// purpose      : to simulate the tic file
// created on   : 7/23/2025 - Tyler
// last modified: 7/23/2025 - Tyler
// --------------------------------------------------------------------

#ifndef TIC_H
#define TIC_H

#include <cstdint>
#include <iostream>

class TicI2C
{
public:
    TicI2C();
    TicI2C(int address);
    void exitSafeStart();
    void setTargetVelocity(int velocity);
    void setTargetPosition(int pos);
    void haltAndHold();
    void haltAndSetPosition(int pos);
    int getCurrentPosition();
    void goHomeForward();
    void resetCommandTimeout();
};

#endif
