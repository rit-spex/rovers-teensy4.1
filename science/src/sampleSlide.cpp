#include "sampleSlide.h"

#include <Arduino.h>
#include "CAN/messages/science.h"
#include "constants.h"
#include "pinout.h"

inline String slideStageToString(SlideStage stage) {
    switch (stage) {
        case SlideStage::Home: return "Home";
        case SlideStage::Collection1: return "Collection 1";
        case SlideStage::Collection2: return "Collection 2";
        case SlideStage::Purge: return "Purge";
        case SlideStage::SampleCache: return "Sample Cache";
        default: return "";
    }
}

SampleSlide::SampleSlide() {
    m_currentStage = SlideStage::Home;
    m_stepper = TicI2C(SS_TIC_ADDR);
}

SampleSlide::~SampleSlide() {
}

void SampleSlide::startUp() {
    m_stepper.exitSafeStart();
    delay(STEPPER_INIT_DELAY_MS);

#if ENABLE_SERIAL
    Serial.println("Sample Slide start up completed");
#endif
    this->goHome();
}

void SampleSlide::updateSubsystems() {
    m_stepper.resetCommandTimeout();
}

void SampleSlide::goHome() {
    goToStage(SlideStage::Home);
}

bool SampleSlide::isHomed() {
    return m_currentStage == SlideStage::Home && !m_stepper.getHomingActive();
}

SlideStage SampleSlide::getStage() {
    return m_currentStage;
}

void SampleSlide::goToStage(SlideStage stage) {
#if ENABLE_SERIAL
    Serial.printf("Sample slide going to %s stage", slideStageToString(stage).c_str());
#endif
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

uint32_t SampleSlide::getStepperPos() {
    // TODO: maybe account for position uncertain
    return m_stepper.getCurrentPosition();
}
