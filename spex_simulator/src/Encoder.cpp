// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : Encoder.cpp
// purpose      : to simulate the encoder file for chassis, creates a thread that will increase the count to emulate the encoder
// created on   : 8/13/2025 - Tyler
// last modified: 8/13/2025 - Tyler
// --------------------------------------------------------------------

#include <Encoder.h>
Encoder::Encoder(int pin1, int pin2)
{
    this->pin1 = pin1;
    this->pin2 = pin2;
    this->counts = 0;
    this->lastCountTime = millis();

    std::cout << "Encoder constructor called" << std::endl;
}

void Encoder::attach(int pin1, int pin2)
{

    this->pin1 = pin1;
    this->pin2 = pin2;

    std::cout << "Encoder attach called with pin1: " << pin1 << " and pin2: " << pin2 << std::endl;
}
long Encoder::read()
{
    // the power set to the wheel, range between - -40,40 to keep it with max RPM
    float power = 0;
    #if BUILD_CHASSIS
        switch(pin1)
        {
            case ENC_A_PIN_1:
                power = (pwm_pin_0-1500)*40.0/500;
                break;
            case ENC_A_PIN_2:
                power = (pwm_pin_1-1500)*40.0/500;
                break;
            case ENC_A_PIN_3:
                power = (pwm_pin_2-1500)*40.0/500;
                break;
            case ENC_A_PIN_4:
                power = (pwm_pin_3-1500)*40.0/500;
                break;
            case ENC_A_PIN_5:
                power = (pwm_pin_4-1500)*40.0/500;
                break;
            case ENC_A_PIN_6:
                power = (pwm_pin_5-1500)*40.0/500;
                break;
        }
    #endif
    //std::cout << "Encoder read called on encoder with pins: "<< pin1 << "lastCount" << std::endl;
    this->counts = this->counts + (millis()-this->lastCountTime)*power;
    this->lastCountTime = millis();
    return this->counts;
}
void Encoder::write(int value)
{
    this->counts = value;
    this->lastCountTime = millis();
    //std::cout << "Encoder write called with value: " << value << std::endl;
}