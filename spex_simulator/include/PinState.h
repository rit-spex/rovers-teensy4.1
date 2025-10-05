#ifndef PIN_STATE_H
#define PIN_STATE_H

#include <unordered_map>

class PinState
{
public:
    struct PinData
    {
        int m_value;
        int m_mode;
    };
    std::unordered_map<int, PinData> m_pinMap;
    int getPinMode(int pin);
    void setPinMode(int pin, int mode);
    int getPinValue(int pin);
    void setPinValue(int pin, int val);
};

#endif // PIN_STATE_H
