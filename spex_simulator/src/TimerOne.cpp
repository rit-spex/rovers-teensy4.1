// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : TimerOne.c
// purpose      : to simulate the timer one file
// created on   : 8/6/2025 - Tyler
// last modified: 8/6/2025 - Tyler
// --------------------------------------------------------------------

#include "TimerOne.h"
#include <stdio.h>

void Timer1_Class::initialize(int time)
{
    printf("Timer1 init time:%d\n", time);
}

void Timer1_Class::start()
{
    printf("Timer1 start\n");
}

void Timer1_Class::pwm(int pin, int duty_cycle)
{
    printf("Timer1 pwm, pin: %d, duty_cycle %d\n", pin, duty_cycle);
}