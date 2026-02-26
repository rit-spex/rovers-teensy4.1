#include "science.h"

#include <Arduino.h>
#include <Tic.h>
#include <Wire.h>
#include <cstdint>

#include "CAN/messages/science.h"
#include "auger.h"
#include "constants.h"
#include "pinout.h"
#include "pump.h"
#include "sampleSlide.h"

Science::Science()
{
}

Science::~Science()
{
}

void Science::startUp()
{
    Serial.begin(9600);
    delay(20);
    Wire.begin();
    delay(20);

    m_auger.startUp();
    m_sampleSlide.startUp();

    pinMode(STATUS_LIGHT_PIN, OUTPUT);

    m_can.startCAN();
    m_can.onMessage<EnableScienceMsg>(MessageID::ENABLE_SCIENCE, [&](const EnableScienceMsg &msg) { this->handleEnableScience(msg); });
    m_can.onMessage<MoveAugerMsg>(MessageID::MOVE_AUGER, [&](const MoveAugerMsg &msg) { this->handleMoveAuger(msg); });
    m_can.onMessage<EnableDrillMsg>(MessageID::ENABLE_DRILL, [&](const EnableDrillMsg &msg) { this->handleEnableDrill(msg); });
    m_can.onMessage<MoveSlideMsg>(MessageID::MOVE_SLIDE, [&](const MoveSlideMsg &msg) { this->handleMoveSlide(msg); });
    m_can.onMessage<EnablePumpMsg>(MessageID::ENABLE_PUMP, [&](const EnablePumpMsg &msg) { this->handleEnablePump(msg); });

#if ENABLE_SERIAL
    Serial.println("Science start up completed");
#endif
}

void Science::updateSubsystems()
{
// #if ENABLE_SERIAL
//     if (Serial.available() > 1)
//     {
//         String input = Serial.readString();
//
//         if (input == "off\n" || input == "disable\n") {
//             disable();
//         } else if (input == "on\n" || input == "enable\n") {
//             enable();
//         } else if (input == "auger up\n") {
//             m_auger.updateHeight(Auger::Direction::Up);
//         } else if (input == "auger down\n") {
//             m_auger.updateHeight(Auger::Direction::Down);
//         } else if (input == "auger home\n") {
//             m_auger.goHome();
//         }
//     }
// #endif

    // Update status light regardless of enabled
    updateStatusLight();

    // Disabled
    if (!m_enabled)
    {
        return;
    }

    // Auger
    m_auger.updateSubsystems();

    // Sample slide
    m_sampleSlide.updateSubsystems();
}

void Science::runBackgroundProcesses()
{
    m_can.poll();
}

void Science::enable()
{
#if ENABLE_SERIAL
    Serial.println("Science enabled");
#endif
    m_enabled = true;
}
void Science::disable()
{
#if ENABLE_SERIAL
    Serial.println("Science disabled");
#endif
    m_enabled = false;
}

bool Science::isEnabled() const
{
    return m_enabled;
}

void Science::updateStatusLight()
{
    unsigned long currentMillis = millis();
    if (!m_enabled)
    {
        digitalWrite(STATUS_LIGHT_PIN, HIGH);
    }
    else if (currentMillis - m_prevMillis >= LED_BLINK_INTERVAL)
    {
        m_prevMillis = currentMillis;
        // Serial.printf("Status light: %d\n", digitalRead(STATUS_LIGHT_PIN));;
        digitalWrite(STATUS_LIGHT_PIN, !digitalRead(STATUS_LIGHT_PIN));
    }
}


void Science::handleEnableScience(const EnableScienceMsg &msg) {
    this->m_enabled = static_cast<bool>(msg.enable);
}

void Science::handleMoveAuger(const MoveAugerMsg &msg) {
    if (static_cast<bool>(msg.home)) {
        this->m_auger.goHome();
        return;
    }

    this->m_auger.updateHeight(static_cast<uint32_t>(msg.position));
}

void Science::handleEnableDrill(const EnableDrillMsg &msg) {
    this->m_auger.updateSpinning(static_cast<bool>(msg.enable));
}

void Science::handleMoveSlide(const MoveSlideMsg &msg) {
    this->m_sampleSlide.goToStage(msg.stage);
}

void Science::handleEnablePump(const EnablePumpMsg &msg) {
    Pump &pump = this->m_pumps[msg.id];
    if (static_cast<bool>(msg.enable)) {
        pump.enable();
    } else {
        pump.disable();
    }
}