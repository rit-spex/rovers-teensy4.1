#ifndef SAMPLE_SLIDE_H
#define SAMPLE_SLIDE_H

class SampleSlide
{
public:
    enum class Position
    {
        Home,
        SampleCache,
        MiddleContainer,
        EndSample,
        OpenSample,
    };

    SampleSlide();
    ~SampleSlide();

    bool isHome(); // returns home sensor status

private:
    Position m_currentPos;
};

#endif // SAMPLE_SLIDE_H
