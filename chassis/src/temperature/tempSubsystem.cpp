// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : tempSubsystem.cppqq
// purpose      : This file defines the temp subsystem class for the rover.
//                This class is responsible for reading the temperature of the thermistors.
// created on   : 1/23/2024 - Ryan Barry
// last modified: 8/14/2025 - Tyler
// --------------------------------------------------------------------

#include "../../include/temperature/tempSubsystem.h"

/*
 * Constructor for the temp subsystem class.
 * Initializes the thermistors.
 */
#if ENABLE_CAN
TempSubsystem::TempSubsystem(CAN *can)
    :
#else
TempSubsystem::TempSubsystem()
    :
#endif
      m_thermistors{Thermistor(0), Thermistor(1), Thermistor(2), Thermistor(3)},
      m_fans{Fan(0), Fan(1), Fan(2), Fan(3)}
#if ENABLE_CAN
      ,
      m_can(can)
#endif
{
}

// @return An array of temperatures measured by each thermistor
float *TempSubsystem::getTemperature()
{
    for (int i = 0; i < NUM_THERMISTORS; i++)
    {
        m_temperature[i] = m_thermistors[i].getTemperature();
    }
    return m_temperature;
}

// Set the power of the fans
void TempSubsystem::setFansPower(int power)
{
    power = std::min(std::max(power, FAN_MIN_PWM),
                     FAN_MAX_PWM); // clamp the power to the range (FAN_MIN_PWM   , FAN_MAX_PWM  )

    for (int i = 0; i < NUM_FANS; i++)
    {
        m_fans[i].setPower(power);
    }
}

void TempSubsystem::updateFans()
{
    getTemperature();
    float avgTemp = 0;
    for (int i = 0; i < NUM_THERMISTORS; i++)
    {
        avgTemp += m_temperature[i];
    }
    avgTemp /= NUM_THERMISTORS;

    if (avgTemp > CHASSIS_MAX_TEMP_C)
    {
        setFansPower(FAN_MAX_PWM);
    }
    else if (avgTemp < CHASSIS_MIN_TEMP_C)
    {
        setFansPower(FAN_MIN_PWM);
    }
    else
    {
        float deltaTemp = CHASSIS_MAX_TEMP_C - CHASSIS_MIN_TEMP_C;
        float deltaPower = FAN_MAX_PWM - FAN_MIN_PWM;

        int power = (avgTemp - CHASSIS_MIN_TEMP_C) / deltaTemp * deltaPower + FAN_MIN_PWM;
        setFansPower(power); // change later
    }
}
