#ifndef DRILL_H
#define DRILL_H

class Drill
{
public:
    enum class Direction
    {
        Forward,
        Backward,
    };

    Drill();
    ~Drill();

    bool isEnabled() const;
    void enable();
    void disable();

    Direction getDir() const;
    void setDir(Direction dir);
    void reverseDir();
    // TODO: write function that actually operates the drill

private:
    bool m_enabled;
    Direction m_dir;
};

#endif // DRILL_H
