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

// TODO: Remove
// #define OUTPUT_MIN 0
// #define OUTPUT_MAX 500

// System Includes
#include <Arduino.h>

// Local Includes
#include "DEBUG.h"

class PIDController {
public:
    // Constructor
    PIDController(double kp, double ki, double kd);

    // Update method
    double update(double targeted_RPM, double current_RPM);

private:
    double kp;
    double ki;
    double kd;
    double integral;
    double previous_error;
};

#endif // PID_CONTROLLER_H
