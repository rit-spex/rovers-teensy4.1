#ifndef AUGER_H
#define AUGER_H

#include "Servo.h"

#include <Tic.h>

class Auger {
public:
    Auger();
    ~Auger();

    void startUp();

    // Returns home sensor status
    bool isHome();
    // Moves auger to home
    void goHome();

    void updateSubsystems();

    void updateDirection();
    void updateSpinning();

private:
    Servo m_drillMotor;
    TicI2C m_stepper;

};

#endif // AUGER_H
