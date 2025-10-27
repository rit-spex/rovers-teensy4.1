#ifndef SAMPLE_SLIDE_H
#define SAMPLE_SLIDE_H

class SampleSlide
{
public:
    // XXX: what happens if we are in between states
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

    Position getPosition();
    void setPosition(Position pos);
    void updatePosition();

private:
    Position m_currentPos;
};

#endif // SAMPLE_SLIDE_H
