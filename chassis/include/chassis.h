// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : chassis.h
// purpose      : This file defines the chassis class for the rover.
//                The chassis is responsible for:
//                  - controlling the drive wheels with encoder feedback
//                  - reading the temperature of the thermistors
// created on   : 1/23/2024 - Ryan Barry
// last modified: 8/14/2025 - Tyler
// --------------------------------------------------------------------

#ifndef CHASSIS_H
#define CHASSIS_H

// System Includes
#include <Arduino.h>
#include <math.h>

// Local Includes
#include "constants.h"
#include "DEBUG.h"
#include "pinout.h"

// All of the subsystems
#if ENABLE_DRIVEBASE
#include "./drivebase/drivebase.h"
#endif

#if ENABLE_TEMP
#include "./temperature/tempSubsystem.h"
#endif

// Libs Includes
#if ENABLE_CAN
#include "CAN.h"
#endif

class Chassis
{
public:
    /*
    * Constructor for the Chassis class.
    * Initializes the drive base, temp subsystem.
    @param pointer to the currentRunCycle
    */
    Chassis(unsigned long *currentCycle);
    ~Chassis();

    // startup for all of the subsystems
    void startUp();

    // increments a time then will blink the status light
    void BlinkStatusLight();

    // updates all of the subsystems
    void updateSubsystems(int timeInterval_ms);

    // run any background process while it is not doing main tasks
    void runBackgroundProcess();

    // disables the teensy
    void disable();

    // check if the mbb is disabled
    bool isDisabled();

// Drives the rover based on the left and right joystick values
#if ENABLE_DRIVEBASE
    void drive(float left_axis, float right_axis);
#endif
private:
    bool m_statusLightOn = false;
    int m_statusLightWait = 0;
    bool m_disabled = false;

#if ENABLE_CAN
    CAN m_can;
#endif

    unsigned long *m_currentCyclePtr;

#if ENABLE_DRIVEBASE
#if ENABLE_CAN
    DriveBase m_drive_base = DriveBase(&m_can);
#else
    DriveBase m_drive_base = DriveBase();
#endif
#endif

#if ENABLE_TEMP
#if ENABLE_CAN
    TempSubsystem m_temp_subsystem = TempSubsystem(&m_can);
#else
    TempSubsystem m_temp_subsystem = TempSubsystem();
#endif
#endif
};

#endif // CHASSIS_H
