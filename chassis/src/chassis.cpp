// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : chassis.cpp
// purpose      : This file defines the chassis class for the rover.
//                The chassis is responsible for:
//                  - controlling the drive wheels with encoder feedback
//                  - reading the temperature of the thermistors
// created on   : 1/23/2024 - Ryan Barry
// last modified: 8/14/2025 - Tyler
// --------------------------------------------------------------------

#include "../include/chassis.h"

void Chassis::startUp()
{
    // set up the status light
    pinMode(STATUS_LIGHT_PIN, OUTPUT);

    // set the status light to stay on
    digitalWrite(STATUS_LIGHT_PIN, HIGH);
    m_statusLightOn = true;

    // setup the timer
    m_statusLEDTimer = IntervalTimer();
    m_statusLEDTimer.begin(Chassis::updateStatusLight, STATUS_LIGHT_FREQUENCY_MS);

    // setup the servos
    for (int motor_idx = 0; motor_idx < NUM_WHEELS; motor_idx++)
    {
        m_wheels[motor_idx].attach(MOTOR_PWM_PINS[motor_idx], MAX_DUTY_CYCLE, MIN_DUTY_CYCLE);
    }

    // make sure that we start at driving at zero
    drive(0.0,0.0);
}

void Chassis::updateStatusLight()
{
    // if the robot is disabled then do not blink the LED, and keep it solid
    if(disabled) 
    {
        digitalWrite(STATUS_LIGHT_PIN, HIGH);
        return;
    }

    // blink the status light every STATUS_LIGHT_FREQUENCY_MS
    m_statusLightOn = !m_statusLightOn;
    digitalWrite(STATUS_LIGHT_PIN, m_statusLightOn);
}

void Chassis::checkHeartbeat()
{
    long currentMillis = millis();
    if (abs(currentMillis - (long)lastROSHeartbeatTime) >= TIMEOUT_DURAITON
            && lastROSHeartbeatTime != 0 && disabled) 
    {
        Log.error("ROS heartbeat timeout at %lu\n", currentMillis);
        disable();
    }

    // after checking the heartbeat send the new status
    can.send(HeartbeatMsg{.source = SubSystemID::CHASSIS, .uptime_ms = millis(), .enabled = !disabled}, MessageID::TEENSY_HEARTBEAT);
}

void Chassis::drive(float left_axis, float right_axis)
{
    // if disabled then make the axis sets to be 0
    if (disabled) 
    {
        left_axis = 0.0;
        right_axis = 0.0;
    }

    // make sure that left and right are capped at -1 to 1
    left_axis = min(1.0, max(-1.0, left_axis));
    right_axis = min(1.0, max(-1.0, right_axis));

    // log the drive info for debugging
    Log.trace("Left Axis: %f Right Axis: %f\n", left_axis, right_axis);

    // find the microseconds for the left and right sides
    int leftMicro = NEUTRAL_DUTY_CYCLE + floor((MAX_DUTY_CYCLE - NEUTRAL_DUTY_CYCLE) * left_axis * MOTOR_LEFT_SIGN);
    int rightMicro = NEUTRAL_DUTY_CYCLE + floor((MAX_DUTY_CYCLE - NEUTRAL_DUTY_CYCLE) * right_axis * MOTOR_RIGHT_SIGN);

    m_wheels[0].writeMicroseconds(leftMicro);
    m_wheels[1].writeMicroseconds(leftMicro);
    m_wheels[2].writeMicroseconds(leftMicro);
    m_wheels[3].writeMicroseconds(rightMicro);
    m_wheels[4].writeMicroseconds(rightMicro);
    m_wheels[5].writeMicroseconds(rightMicro);
}

void Chassis::enable()
{
    disabled = false;
    Log.info("Enable Chassis\n");
}

void Chassis::disable()
{
    // disable the rover and stop everything
    disabled = true;
    updateStatusLight();
    drive(0.0, 0.0);
    Log.info("Disable Chassis\n");
}