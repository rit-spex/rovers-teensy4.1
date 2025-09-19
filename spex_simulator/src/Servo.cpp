// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : Servo.h
// purpose      : to simulate the servo file
// created on   : 7/23/2025 - Tyler
// last modified: 7/23/2025 - Tyler
// --------------------------------------------------------------------

#include <Servo.h>

void Servo::attach(int pin, int min, int max)
{
    this->pin = pin;
    std::cout << "Servo attach called with pin: " << pin << " min: " << min << " max: " << max
              << std::endl;
}

void Servo::attach(int pin)
{
    this->pin = pin;
    std::cout << "Servo attach called with pin: " << pin << std::endl;
}

void Servo::detach()
{
    std::cout << "Servo detach called on pin: " << pin << std::endl;
}

void Servo::writeMicroseconds(int microseconds)
{
    // update the output file
    UpdateFile(PrinterData::PIN, pin, microseconds);

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

    // std::cout << "writeMicroseconds called on pin: " << pin << " micro: " << microseconds
    // <<std::endl;
}

void Servo::write(int microseconds)
{
    // call the other function
    writeMicroseconds(microseconds);
}
