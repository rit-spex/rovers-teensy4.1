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

class Thermistor {
    public:
        /*
        * Constructor for the thermistor class.
        * Initializes the thermistor.
        */
        Thermistor(THERMISTOR_PINS thermistorPin);

        /*
        * @return The temperature measured by the thermistor
        */
        float getTemperature();
    private:
        /*
        * The pin that the thermistor is connected to
        */
        THERMISTOR_PINS m_thermistorPin;
        float m_temperature;
};

#endif //THERMISTOR_H
