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
