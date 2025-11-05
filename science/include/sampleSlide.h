#ifndef SAMPLE_SLIDE_H
#define SAMPLE_SLIDE_H

#include "Tic.h"
class SampleSlide
{
public:
    enum class Position
    {
        Home = 0,
        OpenSample = 1,
        SampleCache = 2,
        MiddleContainer = 3,
        EndSample = 4,
    };

    SampleSlide();
    ~SampleSlide();

    void startUp();
    void updateSubsystems();

    void goHome();
    bool isHomed();

    Position getPosition();
    void goToPosition(Position pos);

private:
    Position m_currentPos;
    TicI2C m_stepper;
};

#endif // SAMPLE_SLIDE_H
