#include "auger.h"

#include "constants.h"
#include "pinout.h"

#include <Arduino.h>
#include <Tic.h>
#include <cstdint>

Auger::Auger()
{
    m_stepper = TicI2C(AUGER_I2C_ADDR);
}

Auger::~Auger()
{
}

void Auger::startUp()
{
    m_stepper.exitSafeStart();
    m_drillMotor.attach(AUGER_DRILL_MOTOR_PIN);
    delay(INIT_DELAY_MS);
    m_drillMotor.write(AUGER_DRILL_IDLE_SIGNAL);

    // Home auger
    goHome();
#if ENABLE_SERIAL
    Serial.println("Auger start up completed");
#endif
}

void Auger::goHome()
{
    m_stepper.goHomeReverse();
#if ENABLE_SERIAL
    Serial.println("Auger began homing");
#endif
}

void Auger::update()
{
    m_stepper.resetCommandTimeout(); // Must be called at least once per second
}

void Auger::setHeight(int32_t pos)
{
    m_stepper.setTargetPosition(pos);
}

void Auger::setSpinning(bool isSpinning)
{
    if (isSpinning)
    {
        m_drillMotor.write(AUGER_DRILL_IDLE_SIGNAL + AUGER_DRILL_SPEED);
#if ENABLE_SERIAL
        Serial.println("Began spinning drill");
#endif
    }
    else
    {
        // Not auging
        m_drillMotor.write(AUGER_DRILL_IDLE_SIGNAL);
#if ENABLE_SERIAL
        Serial.println("Stopped spinning drill");
#endif
    }
    m_motorEnabled = isSpinning;
}

uint32_t Auger::getPos() {
    return m_stepper.getCurrentPosition();
}

bool Auger::isDrillEnabled() {
    return m_motorEnabled;
}
