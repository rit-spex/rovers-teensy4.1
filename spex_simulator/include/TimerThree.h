// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : TimerThree.h
// purpose      : to simulate the timer three file
// created on   : 8/5/2025 - Tyler
// last modified: 8/5/2025 - Tyler
// --------------------------------------------------------------------

#ifndef TIMER_THREE_H
#define TIMER_THREE_H

class Timer3_Class
{
public:
    void initialize(int time);
    void start(void);
    void pwm(int pin, int duty_cycle);
};

static Timer3_Class Timer3;
#endif // TIMER_THREE_H
