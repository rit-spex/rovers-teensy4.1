#include "science.h"

#include <Arduino.h>
#include <Tic.h>
#include <Wire.h>
#include <cstdint>

#include "auger.h"
#include "constants.h"
#include "pinout.h"

Science::Science(unsigned long *currentCyclePtr)
    : m_auger(),
#if ENABLE_CAN
      m_can(currentCyclePtr),
#endif
      m_currentCyclePtr(currentCyclePtr)
{
}

Science::~Science()
{
}

void Science::startUp()
{
    Serial.begin(9600);
    Wire.begin();
    delay(20);
    m_auger.startUp();

    pinMode(STATUS_LIGHT_PIN, OUTPUT);

#if ENABLE_CAN
    m_can = CAN(m_currentCyclePtr);
    m_can.startCAN();
#endif
}

void Science::updateSubsystems()
{
    // Update status light regardless of enabled
    updateStatusLight();

    // Disabled
    if (!m_enabled)
    {
#if ENABLE_SERIAL
        Serial.println("Disabled");
#endif
        return;
    }

#if ENABLE_CAN
    processCANMessages();
#endif

    // Auger
    m_auger.updateSubsystems();
}

void Science::runBackgroundProcesses()
{
#if ENABLE_CAN
    m_can.readMsgBuffer();
#endif
}

void Science::enable()
{
    m_enabled = true;
}
void Science::disable()
{
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
