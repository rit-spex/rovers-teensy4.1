#ifndef SAMPLE_SLIDE_H
#define SAMPLE_SLIDE_H

#include "CAN/messages/science.h"
#include "Tic.h"
class SampleSlide
{
public:
    SampleSlide();
    ~SampleSlide();

    void startUp();
    void updateSubsystems();

    void goHome();
    bool isHomed();

    SlideStage getStage();
    void goToStage(SlideStage pos);

private:
    SlideStage m_currentStage;
    TicI2C m_stepper;
};

#endif // SAMPLE_SLIDE_H
