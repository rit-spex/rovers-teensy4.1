// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : fan.h
// purpose      : controls a single fan on the rover's chassis,
//                needed to cool battery and electronics
// created on   : 8/14/2025 - Tyler
// last modified: 8/14/2025 - Tyler
// --------------------------------------------------------------------

#ifndef FAN_H
#define FAN_H

// system includes
#include <Arduino.h>

// local includes
#include "./pinout.h"
#include "./DEBUG.h"


class Fan
{
    public:
    Fan(uint8_t fan_id);
    void setPower(int pwm_signal);
    //pwm pin to control fan speed
    // four fans
    private:
    uint8_t m_fan_id;
};

#endif //FAN_H