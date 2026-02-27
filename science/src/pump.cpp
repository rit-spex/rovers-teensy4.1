#include "pump.h"

#include "constants.h"
#include <Arduino.h>

Pump::Pump(const uint8_t addr, const int32_t speed) : m_stepper(addr), m_speed(speed)
{
}

Pump::~Pump()
{
}

void Pump::startUp() {
    m_stepper.exitSafeStart();
    delay(INIT_DELAY_MS);
    m_stepper.setTargetVelocity(0);
}

void Pump::update() {
    m_stepper.resetCommandTimeout();
}

void Pump::start() {
    m_stepper.setTargetVelocity(m_speed);
}

void Pump::stop() {
    m_stepper.setTargetVelocity(0);
}

int32_t Pump::getSpeed() const {
    return m_speed;
}

void Pump::setSpeed(int32_t val) {
    m_speed = val;
    // Update speed if currently pumping
    if (m_stepper.getCurrentVelocity() != 0) {
        m_stepper.setTargetVelocity(m_speed);
    }
}
