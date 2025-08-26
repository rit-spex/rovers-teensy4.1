// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : motor.h
// purpose      : controls a single drive motor on the rover's chassis,
//                uses each motor as a servo
// created on   : 8/14/2025 - Tyler
// last modified: 8/14/2025 - Tyler
// --------------------------------------------------------------------

#ifndef MOTOR_H
#define MOTOR_H

// system includes
#include <math.h>
#include <Arduino.h>
#include <Servo.h>

// local includes
#include "./pinout.h"
#include "./constants.h"
#include "./DEBUG.h"

// Motor class for controlling the motors, this is meant to be a generic class for all motors
class Motor 
{
    public:
        Motor(PWM_PINS pwm_pin, int direction);
        ~Motor();
        void setSpeed(float percent);
        float getSpeed();
        void forceStop();
    private:
        Servo m_motor;
        float m_speed;
        int m_direction;

        void updateMotor();
};
#endif //MOTOR_H
