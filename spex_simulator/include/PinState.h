#ifndef PIN_STATE_H
#define PIN_STATE_H

#include <unordered_map>

class PinState
{
public:
    std::unordered_map<int, int> m_pinMap;
    int getPinValue(const int pin);
    void setPinValue(const int pin, const int val);
};

#endif // PIN_STATE_H
