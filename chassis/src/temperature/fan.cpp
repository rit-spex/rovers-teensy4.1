// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : fan.cpp
// purpose      : controls a single fan on the rover's chassis,
//                needed to cool battery and electronics
// created on   : 8/14/2025 - Tyler
// last modified: 8/14/2025 - Tyler
// --------------------------------------------------------------------

#include "../../include/temperature/fan.h"

Fan::Fan(FAN_PINS pin) : m_pin(pin)
{
    pinMode(pin, OUTPUT);
}

void Fan::setPower(int pwm_signal)
{
    analogWrite(m_pin, pwm_signal);
    // four fans
}