// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : TimerOne.c
// purpose      : to simulate the timer one file
// created on   : 8/6/2025 - Tyler
// last modified: 8/6/2025 - Tyler
// --------------------------------------------------------------------

#include "TimerOne.h"
#include "spdlog/spdlog.h"
#include <stdio.h>

void Timer1_Class::initialize(int time)
{
    spdlog::debug("Timer1 init time: {}", time);
}

void Timer1_Class::start()
{
    spdlog::debug("Timer1 start");
}

void Timer1_Class::pwm(int pin, int duty_cycle)
{
    spdlog::debug("Timer1 pwm, pin {}, duty_cycle {}", pin, duty_cycle);
}
