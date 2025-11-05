#include "sampleSlide.h"

SampleSlide::SampleSlide()
{
    m_currentPos = Position::Home;
}

SampleSlide::~SampleSlide()
{
}

SampleSlide::Position SampleSlide::getCurrentPosition()
{
    return m_currentPos;
}
