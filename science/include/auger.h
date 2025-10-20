#ifndef AUGER_H
#define AUGER_H

#include "Servo.h"
#include "constants.h"

#include <Tic.h>
#include <Arduino.h>

class Auger {
public:
    enum class HomingState {
        Idle,
        InProgress,
        Backoff,
        Complete,
        Failed,
    };
    Auger();
    ~Auger();

    void startUp();

    void beginHoming();
    void updateHoming();
    // Has the homing process completed?
    bool isHomed();
    // Returns home sensor status
    bool homeSensorTriggered();

    void updateSubsystems();

    void updateDirection();
    void updateSpinning();

private:
    Servo m_drillMotor;
    TicI2C m_stepper;

    HomingState m_homingState = HomingState::Idle;
    unsigned long m_homingStartTime = 0;

};

#endif // AUGER_H
