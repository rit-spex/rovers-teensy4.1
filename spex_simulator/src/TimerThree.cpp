// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : TimerThree.c
// purpose      : to simulate the timer one file
// created on   : 8/6/2025 - Tyler
// last modified: 8/6/2025 - Tyler
// --------------------------------------------------------------------

#include "TimerThree.h"
#include "spdlog/spdlog.h"
#include <stdio.h>
void Timer3_Class::initialize(int time)
{
    spdlog::debug("Timer3 init time: {}", time);
}

void Timer3_Class::start()
{
    spdlog::debug("Timer3 start");
}

void Timer3_Class::pwm(int pin, int duty_cycle)
{
    spdlog::debug("Timer3 pwm, pin {}, duty_cycle {}", pin, duty_cycle);
}
