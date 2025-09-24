#include "PinState.h"

PinState pinState;

int PinState::getPinValue(const int pin)
{
    return m_pinMap[pin];
}

void PinState::setPinValue(const int pin, const int val)
{
    m_pinMap[pin] = val;
}
