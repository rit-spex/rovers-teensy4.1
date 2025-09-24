#include "PinState.h"

PinState pinState;

int PinState::getPinMode(const int pin)
{
    return m_pinMap[pin].m_mode;
}

void PinState::setPinMode(const int pin, const int mode)
{
    m_pinMap[pin].m_mode = mode;
}

int PinState::getPinValue(const int pin)
{
    return m_pinMap[pin].m_value;
}

void PinState::setPinValue(const int pin, const int val)
{
    m_pinMap[pin].m_value = val;
}
