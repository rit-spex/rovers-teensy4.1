// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : PIDController.cpp
// purpose      : This file contains a class to preform the 
//                caculations needed for PID control, 
//                NOTE: this only preforms calculations doesn't apply them
// created on   : 8/14/2025 - Tyler
// last modified: 8/14/2025 - Tyler
// --------------------------------------------------------------------


#include "../../include/drivebase/PIDController.h"

// Constructor
PIDController::PIDController(double kp, double ki, double kd)
    : kp(kp), ki(ki), kd(kd), integral(0), previous_error(0) {}

// Update method
double PIDController::update(double targeted_RPM, double current_RPM) 
{
    double error = targeted_RPM - current_RPM;
    integral += error;
    double derivative = error - previous_error;
    double output = (kp * error) + (ki * integral) + (kd * derivative);
    previous_error = error;

    #if ENABLE_SERIAL
    // Serial.print("Error: ");
    // Serial.print((float)error);
    // Serial.print(" Output: ");
    // Serial.print((float)output);
    // Serial.println(" ");
    #endif

    return output;
}
