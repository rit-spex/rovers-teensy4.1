#include "auger.h"

#include "constants.h"
#include "pinout.h"

#include <Arduino.h>
#include <Tic.h>

Auger::Auger()
{
    m_stepper = TicI2C(AUGER_TIC_PIN);
}

Auger::~Auger()
{
}

void Auger::startUp()
{
    // Pin states
    pinMode(AUGER_UP_PIN, INPUT_PULLUP);
    pinMode(AUGER_DOWN_PIN, INPUT_PULLUP);
    pinMode(AUGER_SPINNING_PIN, INPUT_PULLDOWN);

    m_stepper.exitSafeStart();
    m_drillMotor.attach(AUGER_DRILL_MOTOR_PIN);

    // Home auger
    goHome();
#if ENABLE_SERIAL
    Serial.println("Auger start up completed");
#endif
}

void Auger::goHome()
{
    m_stepper.goHomeForward();
#if ENABLE_SERIAL
    Serial.println("Auger began homing");
#endif
}

// XXX: Move it all into science updateSubsystems
void Auger::updateSubsystems()
{
    m_stepper.resetCommandTimeout(); // Must be called at least once per second
}

void Auger::updateHeight(Direction dir)
{
    if (m_stepper.getCurrentPosition() >= AUGER_MID_POINT * 2)
    {
        m_stepper.setTargetVelocity(0);
        return;
    }

    switch (dir)
    {
    case Direction::Up:
        m_stepper.setTargetVelocity(AUGER_SPEED);
#if ENABLE_SERIAL
        Serial.println("Auger moving up");
#endif
    case Direction::Down:
        m_stepper.setTargetVelocity(-AUGER_SPEED);
#if ENABLE_SERIAL
        Serial.println("Auger moving down");
#endif
    };
}

void Auger::updateSpinning(bool isSpinning)
{
    if (isSpinning)
    {
        // XXX: what the fuck
        m_drillMotor.write(AUGER_MID_POINT + AUGER_DRILL_SPEED);
#if ENABLE_SERIAL
        Serial.println("Auging");
#endif
    }
    else
    {
        // Not auging
        m_drillMotor.write(AUGER_MID_POINT);
    }
}
