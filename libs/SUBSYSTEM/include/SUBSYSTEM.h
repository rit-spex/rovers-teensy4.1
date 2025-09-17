#ifndef SUBSYSTEM_H
#define SUBSYSTEM_H

class Subsystem {
protected:
    bool m_disabled = false;
public:
    virtual void startUp() = 0;
    virtual void blinkStatusLight() = 0;
    virtual void disable() = 0;
    bool isDisabled();

    virtual ~Subsystem() {}
};

#endif