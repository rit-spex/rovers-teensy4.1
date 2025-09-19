// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : TimerOne.h
// purpose      : to simulate the timer one file
// created on   : 8/5/2025 - Tyler
// last modified: 8/5/2025 - Tyler
// --------------------------------------------------------------------

#ifndef TIMER_ONE_H
#define TIMER_ONE_H

class Timer1_Class
{
public:
    void initialize(int time);
    void start(void);
    void pwm(int pin, int duty_cycle);
};

static Timer1_Class Timer1;

#endif // TIMER_ONE_H