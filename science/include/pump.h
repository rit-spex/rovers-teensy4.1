#ifndef PUMP_H
#define PUMP_H
#include "Tic.h"

class Pump
{
public:
    explicit Pump(const uint8_t addr, const int32_t speed);
    ~Pump();

    void startUp();
    void update();

    void start();
    void stop();
    int32_t getSpeed() const;
    void setSpeed(int32_t val);

private:
    TicI2C m_stepper;
    int32_t m_speed;
};

#endif // PUMP_H
