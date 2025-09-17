#ifndef TEENSY_TEMPLATE_H
#define TEENSY_TEMPLATE_H

class TeensyTemplate {
protected:
    bool m_disabled = false;
public:
    virtual void startUp() = 0;
    virtual void blinkStatusLight() = 0;
    virtual void disable() = 0;
    bool isDisabled();

    virtual ~TeensyTemplate() {}
};

#endif