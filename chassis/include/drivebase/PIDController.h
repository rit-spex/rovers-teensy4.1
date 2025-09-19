// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : PIDController.h
// purpose      : This file contains a class to preform the
//                caculations needed for PID control,
//                NOTE: this only preforms calculations doesn't apply them
// created on   : 8/14/2025 - Tyler
// last modified: 8/14/2025 - Tyler
// --------------------------------------------------------------------

#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

// System Includes
#include <Arduino.h>
#include <cstdint>

// Local Includes
#include "DEBUG.h"
#include "constants.h"

class PIDController
{
public:
    // Constructor
    PIDController(uint8_t PID_id);

    // Update method
    double update(double targeted_RPM, double current_RPM);

private:
    uint8_t m_PID_id;
    double m_kp;
    double m_ki;
    double m_kd;
    double m_integral;
    double m_previous_error;
};

#endif // PID_CONTROLLER_H
