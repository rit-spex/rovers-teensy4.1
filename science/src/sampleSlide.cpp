#include "sampleSlide.h"

#include <Arduino.h>
#include "constants.h"
#include "pinout.h"

char *posToString(SampleSlide::Position pos)
{
    switch (pos) {
        case SampleSlide::Position::Home: {
            return (char *)"Home";
            break;
        }
        case SampleSlide::Position::OpenSample: {
            return (char *)"Open Sample";
            break;
        }
        case SampleSlide::Position::SampleCache: {
            return (char *)"Sample Cache";
            break;
        }
        case SampleSlide::Position::MiddleContainer: {
            return (char *)"Middle Container";
            break;
        }
        case SampleSlide::Position::EndSample: {
            return (char *)"End Sample";
            break;
        }
        default: {
            return (char *)"Unimplemented Position";
            break;
        }
    }
}

SampleSlide::SampleSlide()
{
    m_currentPos = Position::Home;
}

SampleSlide::~SampleSlide()
{
}

void SampleSlide::startUp()
{
    pinMode(SS_TIC_PIN, OUTPUT);
#if ENABLE_SERIAL
    Serial.println("Sample Slide start up completed");
#endif
}

void SampleSlide::updateSubsystems()
{
    m_stepper.resetCommandTimeout();
    goToPosition(Position::EndSample);
}

void SampleSlide::goHome()
{
    goToPosition(Position::Home);
}

bool SampleSlide::isHomed()
{
    return m_currentPos == Position::Home;
}

SampleSlide::Position SampleSlide::getPosition()
{
    return m_currentPos;
}

void SampleSlide::goToPosition(Position pos)
{
#if ENABLE_SERIAL
    Serial.printf("Moving sample slide to %s", posToString(pos));
#endif

    m_currentPos = pos;
    switch (pos) {
        case Position::Home: {
            m_stepper.goHomeReverse();
            break;
        }
        case Position::OpenSample: {
            m_stepper.setTargetPosition(SS_OPEN_SAMPLE);
            break;
        }
        case Position::SampleCache: {
            m_stepper.setTargetPosition(SS_SAMPLE_CACHE);
            break;
        }
        case Position::MiddleContainer: {
            m_stepper.setTargetPosition(SS_MIDDLE_CONTAINER);
            break;
        }
        case Position::EndSample: {
            m_stepper.setTargetPosition(SS_END_SAMPLE);
            break;
        }
        default: {
            break;
        }
    }
}
