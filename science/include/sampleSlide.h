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

    // Returns home sensor status
    bool isHome();
    // Moves sample slide to home
    void goHome();

private:
    Position m_currentPos;
};

#endif // SAMPLE_SLIDE_H
