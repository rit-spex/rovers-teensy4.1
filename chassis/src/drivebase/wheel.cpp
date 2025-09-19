// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : wheel.cpp
// purpose      : This file defines the wheel class for the rover.
//                This class is responsible for controlling each 
//                individual wheel of the rover based on its target speed.
// created on   : 1/23/2024 - Ryan Barry
// last modified: 8/14/2025 - Tyler
// --------------------------------------------------------------------

#include "../../include/drivebase/wheel.h"

#if ENABLE_ENCODER
Wheel::Wheel(uint8_t wheel_id)
    : m_motor(wheel_id), m_encoder(wheel_id), m_pid(wheel_id) {

    this->m_targetRPM = 0;
    this->m_currentRPM = 0;
}
}
#else
Wheel::Wheel(uint8_t wheel_id) :
    m_motor(wheel_id) {
}
#endif

void Wheel::setPercent(float targetPercent)
{
    m_motor.setPercent(targetPercent);
}

#if ENABLE_ENCODER
void Wheel::setRPM(float targetRPM)
{
    this->m_targetRPM = targetRPM;
}

float Wheel::getRPM()
{
    return this->m_currentRPM;
}

/*
* Updates the PID controller for the wheel
*/
void Wheel::updatePID()
{
    this->m_currentRPM = m_direction * this->m_encoder.getRPM();
    float pidOutput = this->m_pid.update(this->m_targetRPM, this->m_currentRPM);
    m_motor.setPercent(pidOutput);
}

#endif

void Wheel::forceStop()
{
    m_motor.forceStop();
}
