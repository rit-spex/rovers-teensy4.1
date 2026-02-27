#include "science.h"

#include <Arduino.h>
#include <Tic.h>
#include <Wire.h>
#include <cstdint>

#include "CAN/message_id.h"
#include "CAN/messages/misc.h"
#include "CAN/messages/science.h"
#include "auger.h"
#include "constants.h"
#include "pinout.h"
#include "pump.h"
#include "sampleSlide.h"

Science::Science() {
}

Science::~Science() {
}

void Science::startUp() {
    Serial.begin(9600);
    delay(20);
    Wire.begin();
    delay(20);

    pinMode(STATUS_LIGHT_PIN, OUTPUT);

    m_can.startCAN();
    m_can.onMessage<EnableScienceMsg>(MessageID::ENABLE_SCIENCE, [&](const EnableScienceMsg &msg) {
        this->handleEnableScience(msg);
    });

    // Setup auger
#ifdef ENABLE_AUGER
    m_auger.startUp();
    m_can.onMessage<MoveAugerMsg>(MessageID::MOVE_AUGER, [&](const MoveAugerMsg &msg) { this->handleMoveAuger(msg); });
    m_can.onMessage<EnableDrillMsg>(MessageID::ENABLE_DRILL, [&](const EnableDrillMsg &msg) {
        this->handleEnableDrill(msg);
    });
#endif

    // Setup sample slide
#ifdef ENABLE_SAMPLE_SLIDE
    m_sampleSlide.startUp();
    m_can.onMessage<MoveSlideMsg>(MessageID::MOVE_SLIDE, [&](const MoveSlideMsg &msg) { this->handleMoveSlide(msg); });
#endif

    // Setup pumps
#ifdef ENABLE_PUMPS
    m_can.onMessage<EnablePumpMsg>(MessageID::ENABLE_PUMP, [&](const EnablePumpMsg &msg) {
        this->handleEnablePump(msg);
    });
    for (auto &pump: m_pumps) {
        pump.startUp();
    }
#endif

    m_startMillis = millis();

#if ENABLE_SERIAL
    Serial.println("Science start up completed");
#endif
}

void Science::updateSubsystems() {
    // Update status light regardless of enabled
    updateStatusLight();

    // Disabled
    if (!m_enabled) {
        return;
    }

    // Auger
#ifdef ENABLE_AUGER
    m_auger.update();
    m_can.send(
        ReadAugerMsg {
            .position = this->m_auger.getPos(),
            .limitSwitch = (uint8_t)false,
        },
        MessageID::READ_AUGER
    );
    m_can.send(
        ReadDrillMsg {
            .enabled = m_auger.isDrillEnabled(),
        },
        MessageID::READ_DRILL
    );
#endif

    // Sample slide
#ifdef ENABLE_SAMPLE_SLIDE
    m_sampleSlide.update();
    m_can.send(
        ReadSlideMsg {
            .stage = m_sampleSlide.getStage(),
            .position = m_sampleSlide.getStepperPos(),
            .limitSwitch = (uint8_t)false,
        },
        MessageID::READ_SLIDE
    );
#endif

    // Pumps
#ifdef ENABLE_PUMPS
    for (size_t i = 0; i < NUM_PUMPS; i++) {
        m_pumps[i].update();
    }
    m_can.send(
        ReadPumpsMsg {
            .pump1Enabled = m_pumps[0].isEnabled(),
            .pump2Enabled = m_pumps[1].isEnabled(),
            .pump3Enabled = m_pumps[2].isEnabled(),
            .pump4Enabled = m_pumps[3].isEnabled()
        },
        MessageID::READ_PUMPS
    );
#endif

    // Send our heartbeat
#if TEENSY_ID == 1
    m_can.send(
        HeartbeatMsg{
            .source = SubSystemID::SCIENCE,
            .uptime_ms = millis() - m_startMillis,
            .enabled = static_cast<uint8_t>(m_enabled)
        },
        MessageID::TEENSY_HEARTBEAT
    );
#endif
}

void Science::runBackgroundProcesses() {
    m_can.poll();
}

void Science::enable() {
#if ENABLE_SERIAL
    Serial.println("Science enabled");
#endif
    m_enabled = true;
}

void Science::disable() {
#if ENABLE_SERIAL
    Serial.println("Science disabled");
#endif
    m_enabled = false;
}

bool Science::isEnabled() const {
    return m_enabled;
}

void Science::updateStatusLight() {
    unsigned long currentMillis = millis();
    if (!m_enabled) {
        digitalWrite(STATUS_LIGHT_PIN, HIGH);
    } else if (currentMillis - m_prevMillis >= LED_BLINK_INTERVAL) {
        m_prevMillis = currentMillis;
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

    this->m_auger.setHeight(static_cast<uint32_t>(msg.position));
}

void Science::handleEnableDrill(const EnableDrillMsg &msg) {
    this->m_auger.setSpinning(static_cast<bool>(msg.enable));
}

void Science::handleMoveSlide(const MoveSlideMsg &msg) {
    this->m_sampleSlide.goToStage(msg.stage);
}

void Science::handleEnablePump(const EnablePumpMsg &msg) {
    Pump &pump = this->m_pumps[msg.id];
    if (static_cast<bool>(msg.enable)) {
        pump.start();
    } else {
        pump.stop();
    }
}
