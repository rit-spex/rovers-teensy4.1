// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : drivebase.h
// purpose      : This file defines the drive base class for the rover.
//                This class is responsible for controlling the 
//                rover's wheels based on the target velocity 
//                transmitted over CAN.
// created on   : 1/23/2024 - Ryan Barry
// last modified: 8/14/2025 - Tyler
// --------------------------------------------------------------------

#ifndef DRIVE_BASE_H
#define DRIVE_BASE_H

// System Includes
#include <math.h>

// Local Includes
#include "./constants.h"
#include "./DEBUG.h"
#include "./pinout.h"
#include "wheel.h"

// Libs Includes
#ifdef ENABLE_CAN
#include "CAN.h"
#endif

class DriveBase {
    public:
        #if ENABLE_CAN
            DriveBase(CAN *can);
        #else
            DriveBase();
        #endif

        #if ENABLE_ENCODER
        // Updates the RPM of the rover's wheels. motor final percent is calculated by the PID controller
        void updateRPM();
        #else
        // Updates the percent of the rover's wheel.
        void updateSingleWheelPercent(int wheelIndex, float targetPercent);
        #endif
        void drive(float left_axis, float right_axis);

        // stop the wheels immedately
        void forceStop();
    private:
        // An array of the rover's wheels
        Wheel m_wheels[NUM_WHEELS];

        // CAN object for the rover
        #if ENABLE_CAN
        CAN *m_CAN;
        #endif

        #if ENABLE_ENCODER

        // An array of the target RPMs corresponding to each wheel
        float m_targetRPM[NUM_WHEELS];

        #if ENABLE_CAN
        void getTargetRPM();
        #endif
        #endif
};
#endif
