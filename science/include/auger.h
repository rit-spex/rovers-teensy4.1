#ifndef AUGER_H
#define AUGER_H

#include "Servo.h"
#include "constants.h"

#include <Arduino.h>
#include <Tic.h>
#include <cstdint>

// Tic Forward = Down in the world
// Home is up or Tic Backward
class Auger
{
public:
    Auger();
    ~Auger();

    enum class Direction
    {
        Up,
        Down,
    };

    void startUp();

    void goHome();
    bool isHomed();

    void updateSubsystems();

    void updateHeight(int32_t pos);
    void updateSpinning(bool isSpinning);

private:
    Servo m_drillMotor;
    TicI2C m_stepper;
};

#endif // AUGER_H
