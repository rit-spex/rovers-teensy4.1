#include "auger.h"

#include "pinout.h"
#include "constants.h"

#include <Arduino.h>
#include <Tic.h>

Auger::Auger() {}

void Auger::startUp() {
    pinMode(AUGER_UP_PIN, INPUT_PULLUP);
    pinMode(AUGER_DOWN_PIN, INPUT_PULLUP);
    pinMode(AUGER_SPINNING_PIN, INPUT_PULLDOWN);
    m_stepper.exitSafeStart();
    m_drillMotor.attach(AUGER_DRILL_MOTOR_PIN);
}

void Auger::updateSubsystems() {
    updateDirection();
    m_stepper.resetCommandTimeout(); // Must be called at least once per second
    updateSpinning();
}

void Auger::updateDirection() {
    int up = digitalRead(AUGER_UP_PIN);
    int down = digitalRead(AUGER_DOWN_PIN);
    if (up == LOW) {
        m_stepper.setTargetVelocity(AUGER_SPEED);
#if ENABLE_SERIAL
        Serial.println("Auger moving up");
#endif
    } else if (down == LOW) {
        m_stepper.setTargetVelocity(-AUGER_SPEED);
#if ENABLE_SERIAL
        Serial.println("Auger moving down");
#endif
    } else {
        m_stepper.setTargetVelocity(0);
    }
}

void Auger::updateSpinning() {
    int isSpinning = digitalRead(AUGER_SPINNING_PIN);
    if (isSpinning == HIGH) {
        m_drillMotor.write(AUGER_MID_POINT + AUGER_DRILL_SPEED);
#if ENABLE_SERIAL
        Serial.println("Auging")
#endif
    } else {
        m_drillMotor.write(AUGER_MID_POINT);
    }
}

