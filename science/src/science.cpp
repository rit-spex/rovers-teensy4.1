#include "science.h"

#include <Arduino.h>
#include <Tic.h>
#include <Wire.h>

#include "constants.h"
#include "pinout.h"

Science::Science(unsigned long *currentCyclePtr)
    :
    m_auger(),
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

bool Science::isDisabled() const
{
    return !m_enabled;
}

void Science::updateStatusLight()
{
    unsigned long currentMillis = millis();
    if (isDisabled())
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
    }
}
#endif
