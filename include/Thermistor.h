/*
File: thermistor.h
Author: Ryan Barry
Date Created: 1/23/2024

This file defines the thermistor class for the rover.
This class is responsible for reading the temperature of a thermistor.
*/

#ifndef THERMISTOR_H
#define THERMISTOR_H

#include "DEBUG.h"
#include "Pinout.h"
#include <math.h>

#if ENABLE_SIMULATOR
#include "../TestSystem/Simulator.h"
#else
#include <Wire.h>
#include <Arduino.h>
#endif

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

#endif
