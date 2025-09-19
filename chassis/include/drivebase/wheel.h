// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : wheel.h
// purpose      : This file defines the wheel class for the rover.
//                This class is responsible for controlling each 
//                individual wheel of the rover based on its target speed.
// created on   : 1/23/2024 - Ryan Barry
// last modified: 8/14/2025 - Tyler
// --------------------------------------------------------------------

#ifndef WHEEL_H
#define WHEEL_H

// Local Includes
#include "motor.h"
#include "quadDecoder.h"
#include "PIDController.h"

#include "./pinout.h"
#include "./constants.h"
#include "./DEBUG.h"

class Wheel 
{
    public:
        /*
        * Constructor for the wheel class
        * @param wheel_id: which wheel is the current one
        */
        Wheel(uint8_t wheel_id);

        /*
        * Adjust's the PWM signal to the wheel to match the target percent
        * @param targetPercent The target percent of the wheel
        */
        void setPercent(float targetPercent);

        #if ENABLE_ENCODER
        void setRPM(float targetRPM);

        /*
        * Gets the current RPM of the wheel
        * @return The current RPM of the wheel
        */
        float getRPM();

        /*
        * Updates the PID controller for the wheel
        */
        void updatePID();
        #endif

        void forceStop();

    private:

        Motor m_motor;

        int m_direction;

        #if ENABLE_ENCODER
        QuadratureDecoder m_encoder;
        PIDController m_pid;

        float m_targetRPM;
        float m_currentRPM;
        #endif
};

#endif // WHEEL_H
