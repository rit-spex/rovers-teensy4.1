#ifndef SAMPLE_SLIDE_H
#define SAMPLE_SLIDE_H

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

    Position getCurrentPosition();
    void moveToPosition();

private:
    Position m_currentPos;
};

#endif // SAMPLE_SLIDE_H
