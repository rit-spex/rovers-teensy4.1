#include "sampleSlide.h"

#include <Arduino.h>
#include "CAN/messages/science.h"
#include "constants.h"
#include "pinout.h"

SampleSlide::SampleSlide()
{
    m_currentStage = SlideStage::Home;
}

SampleSlide::~SampleSlide()
{
}

void SampleSlide::startUp()
{
    pinMode(SS_TIC_PIN, OUTPUT);
    m_stepper.exitSafeStart();
#if ENABLE_SERIAL
    Serial.println("Sample Slide start up completed");
#endif
    this->goHome();
}

void SampleSlide::updateSubsystems()
{
    m_stepper.resetCommandTimeout();
}

void SampleSlide::goHome()
{
    goToStage(SlideStage::Home);
}

bool SampleSlide::isHomed()
{
    return m_currentStage == SlideStage::Home;
}

SlideStage SampleSlide::getStage()
{
    return m_currentStage;
}

void SampleSlide::goToStage(SlideStage stage)
{
    m_currentStage = stage;
    switch (stage) {
        case SlideStage::Home: {
            m_stepper.goHomeReverse();
            break;
        }
        case SlideStage::Collection1: {
            m_stepper.setTargetPosition(SS_COLLECTION1_POS);
            break;
        }
        case SlideStage::Collection2: {
            m_stepper.setTargetPosition(SS_COLLECTION2_POS);
            break;
        }
        case SlideStage::Purge: {
            m_stepper.setTargetPosition(SS_PURGE_POS);
            break;
        }
        case SlideStage::SampleCache: {
            m_stepper.setTargetPosition(SS_SAMPLE_CACHE_POS);
            break;
        }
        default: {
            break;
        }
    }
}
