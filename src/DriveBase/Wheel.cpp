#include "../../include/Wheel.h"

#if ENABLE_ENCODER
Wheel::Wheel(PWM_PINS pwm_pin, ENC_A_PINS enc_A_pin, ENC_B_PINS enc_B_pin, double kp, double ki, double kd) 
     : m_motor(pwm_pin), m_encoder(enc_A_pin, enc_B_pin), m_pid(kp, ki, kd){

     this->m_targetRPM = 0;
     this->m_currentRPM = 0;
}
#else
Wheel::Wheel(PWM_PINS pwm_pin):
    m_motor(pwm_pin){}
#endif

void Wheel::setSpeed(float targetSpeed) 
{
    m_motor.setSpeed(targetSpeed);
}

#if ENABLE_ENCODER
void Wheel::setRPM(float targetRPM)
{
    this->m_targetRPM = targetRPM;
}

float Wheel::getRPM()
{
    return this->m_currentRPM;
}

/*
* Updates the PID controller for the wheel
*/
void Wheel::updatePID(int timeInterval_ms)
{
    this->m_currentRPM = this->m_encoder.getRPM(timeInterval_ms);
    float pidOutput = this->m_pid.update(this->m_targetRPM, this->m_currentRPM);
    this->setSpeed(pidOutput);
}

#endif