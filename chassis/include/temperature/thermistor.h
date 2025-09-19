// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : tempSubsystem.h
// purpose      : This file defines the temp subsystem class for the rover.
//                This class is responsible for reading the temperature of the thermistors.
// created on   : 1/23/2024 - Ryan Barry
// last modified: 8/14/2025 - Tyler
// --------------------------------------------------------------------

#ifndef THERMISTOR_H
#define THERMISTOR_H

// system includes
#include <Arduino.h>
#include <math.h>
#include <Wire.h>

// local includes
#include "./DEBUG.h"
#include "./pinout.h"

class Thermistor
{
public:
    /*
     * Constructor for the thermistor class.
     * Initializes the thermistor.
     */
    Thermistor(uint8_t thermistor_id);

    /*
     * @return The temperature measured by the thermistor
     */
    float getTemperature();

private:
    // the id number of the thermistor, matches with fan_id, used to get pin
    uint8_t m_thermistor_id;

    // the current temperature
    float m_temperature;
};

#endif // THERMISTOR_H
