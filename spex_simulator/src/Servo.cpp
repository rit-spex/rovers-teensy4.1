// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : Servo.h
// purpose      : to simulate the servo file
// created on   : 7/23/2025 - Tyler
// last modified: 7/23/2025 - Tyler
// --------------------------------------------------------------------

#include "Servo.h"

#include "spdlog/spdlog.h"
#include "PinState.h"

extern PinState pinState;

void Servo::attach(int pin, int min, int max)
{
    this->pin = pin;
    spdlog::debug("Servo attach called with pin: {} min: {} max: {}", pin, min, max);
}

void Servo::attach(int pin)
{
    this->pin = pin;
    spdlog::debug("Servo attach called with pin: {}", pin);
}

void Servo::detach()
{
    spdlog::debug("Servo detach called on pin: {}", pin);
}

void Servo::writeMicroseconds(int microseconds)
{
    // update the output file
    updateFile(PrinterData::PIN, pin, microseconds);
    pinState.setPinValue(pin, microseconds);

    // update global file
#if BUILD_CHASSIS
    switch (pin)
    {
    case MOTOR_PWM_PIN_1:
        pwm_pin_0 = microseconds;
        break;
    case MOTOR_PWM_PIN_2:
        pwm_pin_1 = microseconds;
        break;
    case MOTOR_PWM_PIN_3:
        pwm_pin_2 = microseconds;
        break;
    case MOTOR_PWM_PIN_4:
        pwm_pin_3 = microseconds;
        break;
    case MOTOR_PWM_PIN_5:
        pwm_pin_4 = microseconds;
        break;
    case MOTOR_PWM_PIN_6:
        pwm_pin_5 = microseconds;
        break;
    }
#endif

    // spdlog::debug("writeMicroseconds called on pin: {} micro: {}", pin, microseconds);
}

void Servo::write(int microseconds)
{
    // call the other function
    writeMicroseconds(microseconds);
}
