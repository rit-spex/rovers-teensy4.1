// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : TimerThree.c
// purpose      : to simulate the timer one file
// created on   : 8/6/2025 - Tyler
// last modified: 8/6/2025 - Tyler
// --------------------------------------------------------------------

#include "TimerThree.h"
#include <stdio.h>
void Timer3_Class::initialize(int time)
{
    printf("Timer3 init time:%d\n", time);
}

void Timer3_Class::start()
{
    printf("Timer3 start\n");
}

void Timer3_Class::pwm(int pin, int duty_cycle)
{
    printf("Timer3 pwm, pin: %d, duty_cycle %d\n", pin, duty_cycle);
}