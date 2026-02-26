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

    m_can.poll();

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
#if ENABLE_CAN
    m_can.readMsgBuffer();
#endif
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
    Pump pump = this->m_pumps[msg.id];
    if (static_cast<bool>(msg.enable)) {
        pump.enable();
    } else {
        pump.disable();
    }
}


#if ENABLE_CAN
void Science::processCANMessages()
{
    if (m_can.isNewMessage(CAN::E_STOP))
    {
        disable();
        return;
    }

    for (int i = 20; i < 30; i++)
    {
        if (!m_can.isNewMessage((CAN::Message_ID)i))
        {
            continue;
        }

        uint8_t *data;
        data = m_can.getUnpackedData((CAN::Message_ID)i);
#if ENABLE_SERIAL
        Serial.printf("ID %d: [%d, %d]\n", i, data[0], data[1]);
#endif
        CAN::Message_ID msgId =  static_cast<CAN::Message_ID>(i);
        switch (msgId)
        {
            case CAN::Message_ID::ENABLE_SCIENCE: {
                if (!(bool)data[0])
                {
                    disable();
                }
                break;
            }
            case CAN::Message_ID::MOVE_AUGER: {
                Auger::Direction dir = (Auger::Direction)data[1];
                m_auger.updateHeight(dir);
                break;
            }
            case CAN::Message_ID::HOME_AUGER: {
                m_auger.goHome();
                break;
            }
            case CAN::Message_ID::ENABLE_DRILL: {
                m_auger.updateSpinning((bool)data[1]);
                break;
            }
            case CAN::Message_ID::MOVE_SLIDE: {
                SampleSlide::Position pos = (SampleSlide::Position)data[1];
                m_sampleSlide.goToPosition(pos);
                break;
            }
            default: {
#if ENABLE_SERIAL
                Serial.printf("CAN message type not accounted for %d\n", i);
#endif
                disable();
                break;
            }
        }
    }
}
#endif
