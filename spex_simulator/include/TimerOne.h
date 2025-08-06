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

class timer1
{
    public:
        void initialize(void);
        void start(void);
        void pwm(int pin, int duty_cycle);
}

static timer1 Timer1;

#endif //TIMER_ONE_H