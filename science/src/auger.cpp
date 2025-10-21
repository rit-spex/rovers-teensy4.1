#include "auger.h"

#include "constants.h"
#include "pinout.h"

#include <Arduino.h>
#include <Tic.h>

Auger::Auger()
{
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
    pinMode(AUGER_HOME_SENSOR_PIN, INPUT_PULLUP);

    m_stepper.exitSafeStart();
    m_drillMotor.attach(AUGER_DRILL_MOTOR_PIN);

    // Home auger
    beginHoming();
}

void Auger::beginHoming()
{
    m_homingState = HomingState::InProgress;
    m_homingStartTime = millis();
    // Start moving background
    m_stepper.setTargetVelocity(-AUGER_HOME_SPEED);
#if ENABLE_SERIAL
    Serial.println("Auger began homing");
#endif
}

void Auger::updateHoming()
{
    switch (m_homingState)
    {
    case HomingState::InProgress:
        m_stepper.resetCommandTimeout();

        // Is at home sensor
        if (homeSensorTriggered())
        {
            // Set as internal 0
            m_stepper.haltAndHold();
            m_stepper.haltAndSetPosition(0);

            // Begin backing off
            m_homingState = HomingState::Backoff;
            m_stepper.setTargetPosition(AUGER_HOME_BACKOFF);
#if ENABLE_SERIAL
            Serial.println("Auger homed");
            Serial.println("Auger backing off");
#endif
        }
        else if (millis() - m_homingStartTime > AUGER_HOME_MAX_MILLIS)
        {
            // if homing taking too long
            m_stepper.haltAndHold();
            m_homingState = HomingState::Failed;
#if ENABLE_SERIAL
            Serial.println("Auger homing failed");
#endif
        }
        break;
    case HomingState::Backoff:
        // We've backed off enough for sensor to not trigger anymore
        if (!homeSensorTriggered())
        {
            m_homingState = HomingState::Complete;
#if ENABLE_SERIAL
            Serial.println("Auger homing complete");
#endif
        }
        break;
    case HomingState::Failed:
    case HomingState::Complete:
    case HomingState::Idle:
        // do nothing
        break;
    }
}

bool Auger::isHomed()
{
    return m_homingState == HomingState::Complete;
}

bool Auger::homeSensorTriggered()
{
    // Assuming LOW when magnet is detected
    return digitalRead(AUGER_HOME_SENSOR_PIN) == LOW;
}

void Auger::updateSubsystems()
{
    // Homing takes priority over other movement
    if (m_homingState == HomingState::InProgress || m_homingState == HomingState::Backoff)
    {
        updateHoming();
    }
    else
    {
        updateDirection();
        updateSpinning();
    }

    m_stepper.resetCommandTimeout(); // Must be called at least once per second
}

void Auger::updateDirection()
{
    int up = digitalRead(AUGER_UP_PIN);
    int down = digitalRead(AUGER_DOWN_PIN);

    if (up == LOW)
    {
        m_stepper.setTargetVelocity(AUGER_SPEED);
#if ENABLE_SERIAL
        Serial.println("Auger moving up");
#endif
    }
    else if (down == LOW)
    {
        m_stepper.setTargetVelocity(-AUGER_SPEED);
#if ENABLE_SERIAL
        Serial.println("Auger moving down");
#endif
    }
    else
    {
        m_stepper.setTargetVelocity(0);
    }
}

void Auger::updateSpinning()
{
    int isSpinning = digitalRead(AUGER_SPINNING_PIN);
    if (isSpinning == HIGH)
    {
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
