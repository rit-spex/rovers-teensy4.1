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

Fan::Fan(uint8_t fan_id) : m_fan_id(fan_id)
{
    pinMode(FAN_PINS[fan_id], OUTPUT);
}

void Fan::setPower(int pwm_signal)
{
    analogWrite(FAN_PINS[m_fan_id], pwm_signal);
    // four fans
}