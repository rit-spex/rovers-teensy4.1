// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : tempSubsystem.h
// purpose      : This file defines the temp subsystem class for the rover.
//                This class is responsible for reading the temperature of the thermistors.
// created on   : 1/23/2024 - Ryan Barry
// last modified: 8/14/2025 - Tyler
// --------------------------------------------------------------------

#ifndef TEMP_SUBSYSTEM_H
#define TEMP_SUBSYSTEM_H

// system includes
#include <math.h>

// local includes
#include "./constants.h"
#include "./pinout.h"
#include "./DEBUG.h"
#include "fan.h"
#include "thermistor.h"

#if ENABLE_CAN
#include "CAN.h"
#endif

class TempSubsystem
{
public:
#if ENABLE_CAN
    TempSubsystem(CAN *can);
#else
    TempSubsystem();
#endif

    float *getTemperature();
    void setFansPower(int power);
    /*
     * Update the temperature and fan power
     */
    void updateFans(void);

private:
    // Array of Thermistor objects
    Thermistor m_thermistors[NUM_THERMISTORS];

    // Array of Fan objects
    Fan m_fans[NUM_FANS];

    // Array of temperature readings
    float m_temperature[NUM_THERMISTORS];

#if ENABLE_CAN
    // Pointer to the CAN object
    CAN *m_can;
#endif
};

#endif