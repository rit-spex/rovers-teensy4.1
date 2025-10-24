#ifndef AUGER_H
#define AUGER_H

#include "Servo.h"
#include "constants.h"

#include <Arduino.h>
#include <Tic.h>

class Auger
{
public:
    Auger();
    ~Auger();

    void startUp();

    void goHome();
    bool isHomed();

    void updateSubsystems();

    void updateDirection();
    void updateSpinning();

private:
    Servo m_drillMotor;
    TicI2C m_stepper;
};

#endif // AUGER_H
