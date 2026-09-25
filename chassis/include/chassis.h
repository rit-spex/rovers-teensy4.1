// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : chassis.h
// purpose      : This file defines the chassis class for the rover.
//                The chassis is responsible for:
//                  - controlling the drive wheels with encoder feedback
//                  - reading the temperature of the thermistors
// created on   : 1/23/2024 - Ryan Barry
// last modified: 8/14/2025 - Tyler
// --------------------------------------------------------------------

#ifndef CHASSIS_H
#define CHASSIS_H

// System Includes
#include <Arduino.h>
#include <math.h>
#include <cmath>
#include <Servo.h>

// Local Includes
#include "CAN/messages/chassis.h"
#include "CAN/messages/misc.h"
#include "CAN/CAN.h"
#include "CAN/message_id.h"
#include "constants.h"
#include "pinout.h"
#include "globals.h"
#include "ArduinoLog.h"

// Libs Includes
#include "CAN/CAN.h"

namespace Chassis 
{
    // startup for all of the subsystems
    void startUp();

    // increments a time then will blink the status light
    void updateStatusLight();

    // checks that the heartbeat is valid
    void checkHeartbeat();

    // enables the teensy
    void enable();

    // disables the teensy
    void disable();

    // Drives the rover based on the left and right joystick values
    void drive(float left_axis, float right_axis);
};

#endif // CHASSIS_H
