// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : motor.cpp
// purpose      : controls a single drive motor on the rover's chassis,
//                uses each motor as a servo
// created on   : 8/14/2025 - Tyler
// last modified: 8/14/2025 - Tyler
// --------------------------------------------------------------------

#include "../../include/drivebase/motor.h"

// constructor
Motor::Motor(uint8_t motor_id)
{
    m_motor_id = motor_id;
    m_motor.attach(MOTOR_PWM_PINS[motor_id], SPARK_MAX_MIN_DUTY_CYCLE,
                   SPARK_MAX_MAX_DUTY_CYCLE); // Assuming 'motor' is a member variable of the Motor class
    m_currPercent = 0;
    m_direction = MOTORS_DIR[m_motor_id];
}

Motor::~Motor()
{
    // clear the motor pin
    m_motor.detach();
}

// write to the motor
void Motor::setPercent(float wantedPercent)
{
    // First check if the target percent is within the bounds of -1 to 1
    if (wantedPercent < -PERCENT_MAX)
    {
        wantedPercent = -PERCENT_MAX;
    }
    else if (wantedPercent > PERCENT_MAX)
    {
        wantedPercent = PERCENT_MAX;
    }
    else
    {
        wantedPercent = wantedPercent;
    }

    if (m_currPercent > 0)
    {
        if (wantedPercent > (m_currPercent + SPARK_MAX_RAMP_UP_PER_CYCLE))
        {
            m_currPercent = m_currPercent + SPARK_MAX_RAMP_UP_PER_CYCLE;
        }
        else if (wantedPercent < (m_currPercent - SPARK_MAX_RAMP_DOWN_PER_CYCLE))
        {
            m_currPercent = m_currPercent - SPARK_MAX_RAMP_DOWN_PER_CYCLE;
        }
        else
        {
            m_currPercent = wantedPercent;
        }
    }
    else if (m_currPercent < 0)
    {
        if (wantedPercent < (m_currPercent - SPARK_MAX_RAMP_UP_PER_CYCLE))
        {
            m_currPercent = m_currPercent - SPARK_MAX_RAMP_UP_PER_CYCLE;
        }
        else if (wantedPercent > (m_currPercent + SPARK_MAX_RAMP_DOWN_PER_CYCLE))
        {
            m_currPercent = m_currPercent + SPARK_MAX_RAMP_DOWN_PER_CYCLE;
        }
        else
        {
            m_currPercent = wantedPercent;
        }
    }
    else
    {
        if (SPARK_MAX_RAMP_UP_PER_CYCLE < wantedPercent)
        {
            m_currPercent = m_currPercent + SPARK_MAX_RAMP_UP_PER_CYCLE;
        }
        else if (SPARK_MAX_RAMP_UP_PER_CYCLE < -wantedPercent)
        {
            m_currPercent = m_currPercent - SPARK_MAX_RAMP_UP_PER_CYCLE;
        }
        else
        {
            m_currPercent = wantedPercent;
        }
    }

    updateMotor();
}

// return the percent that the motor is set to
float Motor::getPercent()
{
    return m_currPercent;
}

void Motor::forceStop()
{
    m_currPercent = 0;
    updateMotor();
}

void Motor::updateMotor()
{
    // If the target percent is negative, set the PWM duty cycle to the reverse range from 1500(0%) to 1000(-100%)
    if (m_currPercent < 0)
    {
        m_motor.writeMicroseconds(
            SPARK_MAX_NEUTRAL_DUTY_CYCLE -
            floor((SPARK_MAX_MIN_DUTY_CYCLE - SPARK_MAX_NEUTRAL_DUTY_CYCLE) * m_currPercent * m_direction));
    }
    // If the target percent is positive, set the PWM duty cycle to the forward range from 1500(0%) to 2000(100%)
    else if (m_currPercent > 0)
    {
        m_motor.writeMicroseconds(
            SPARK_MAX_NEUTRAL_DUTY_CYCLE +
            floor((SPARK_MAX_MAX_DUTY_CYCLE - SPARK_MAX_NEUTRAL_DUTY_CYCLE) * m_currPercent * m_direction));
    }
    // If the target percent is 0, set the PWM duty cycle to SPARK_MAX_NEUTRAL_DUTY_CYCLE
    else
    {
        m_motor.writeMicroseconds(SPARK_MAX_NEUTRAL_DUTY_CYCLE);
    }
}
