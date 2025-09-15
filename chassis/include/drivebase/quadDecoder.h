// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : quadDecoder.h
// purpose      : Defines a class to read from a quad encoder can also
//                find the rpm from using time elapsed
// created on   : 8/14/2025 - Tyler
// last modified: 8/14/2025 - Tyler
// --------------------------------------------------------------------

#ifndef QUADDECODER_H
#define QUADDECODER_H

// System Includes
#include <Encoder.h>

// Local Includes
#include "./pinout.h"
#include "./constants.h"
#include "./DEBUG.h"

// TODO: Remove Me
#define ENCODER_SAVE_SIZE 5

class QuadratureDecoder 
{
    public:
        QuadratureDecoder(uint8_t encoder_id);
  
        void begin();

        // enter the encoder data to the save data
        void updateCount();

        float getRPM();
        // float getRPM();

    private:
        // the physical encoder
        Encoder m_encoder;
        uint8_t m_encoder_id;

        unsigned long m_lastTime;

        // the last x counts from the encoder
        long m_count[ENCODER_SAVE_SIZE];

        // the last x time interval from the encoder
        long m_timeInterval[ENCODER_SAVE_SIZE];

        // the currentHead of the save data
        int m_currentHead;
};

#endif