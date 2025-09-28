// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : quadDecoder.cpp
// purpose      : Defines a class to read from a quad encoder can also
//                find the rpm from using time elapsed
// created on   : 8/14/2025 - Tyler
// last modified: 8/14/2025 - Tyler
// --------------------------------------------------------------------

#include "../../include/drivebase/quadDecoder.h"

QuadratureDecoder::QuadratureDecoder(uint8_t encoder_id)
    : m_encoder(ENC_A_PINS[encoder_id], ENC_A_PINS[encoder_id]), m_encoder_id(encoder_id)
{
    // set the time to now
    m_lastTime = millis();

    // set the current head to the start
    m_currentHead = 0;

    // empty the saved data
    for (int i = 0; i < ENCODER_SAVE_SIZE; i++)
    {
        m_count[i] = 0;
        m_timeInterval[i] = 0;
    }
}

// TODO: REMOVE
// IS THIS NEEDED?
void QuadratureDecoder::begin()
{
    m_encoder.write(0);
}

// update the count of the encoder
void QuadratureDecoder::updateCount()
{
    // enter the current count and time into the save data
    this->m_count[m_currentHead] = this->m_encoder.read();
    this->m_timeInterval[m_currentHead] = millis() - m_lastTime; // millis() - UPDATE_RATE_MS * time_interval_ms;
    this->m_lastTime = millis();

    // reset the encoder count to 0
    this->m_encoder.write(0);

    // update the head of the array
    m_currentHead++;
    if (m_currentHead >= ENCODER_SAVE_SIZE)
    {
        m_currentHead = 0;
    }
}

// get the RPM from the encoder
float QuadratureDecoder::getRPM()
{
    // // get the current count of the encoder and reset the count
    updateCount();

    // calculate the total time
    float totalTime = 0;
    for (int i = 0; i < ENCODER_SAVE_SIZE; i++)
    {
        totalTime += this->m_timeInterval[i];
    }

    // prevent return /0
    if (totalTime == 0)
    {
        return 0;
    }

    // calculate the total counts
    float totalCounts = 0;
    for (int i = 0; i < ENCODER_SAVE_SIZE; i++)
    {
        totalCounts += this->m_count[i];
    }

    // RPM = rotations/min = (totalCount/counts_per_rotation)/(time_interval_ms/milliseconds_per_minute)
    // RPM = (totalCounts * milliseconds_per_minute)/(counts_per_rotation * time_interval_ms)
    return (totalCounts * MS_IN_MIN) / (totalTime * COUNTS_PER_REV);
}
