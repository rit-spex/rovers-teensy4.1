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

    void startUp();

    void goHome();

    void update();

    void setHeight(int32_t pos);
    void setSpinning(bool isSpinning);

    bool isDrillEnabled();

    uint32_t getPos();

private:
    Servo m_drillMotor;
    bool m_motorEnabled = false;
    TicI2C m_stepper;
};

#endif // AUGER_H
