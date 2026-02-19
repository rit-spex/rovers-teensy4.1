// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : chassis.cpp
// purpose      : This file defines the chassis class for the rover.
//                The chassis is responsible for:
//                  - controlling the drive wheels with encoder feedback
//                  - reading the temperature of the thermistors
// created on   : 1/23/2024 - Ryan Barry
// last modified: 8/14/2025 - Tyler
// --------------------------------------------------------------------

#include "../include/chassis.h"
#include "CAN/CAN.h"
#include "CAN/message_id.h"
#include "CAN/messages/misc.h"
#include "CAN/messages/chassis.h"

#if ENABLE_CAN
Chassis::Chassis(unsigned long *currentCycle) : m_currentCyclePtr(currentCycle)
{
}
#else
Chassis::Chassis(unsigned long *currentCycle) : m_currentCyclePtr(currentCycle)
{
}
#endif

Chassis::~Chassis()
{
}

void Chassis::startUp()
{
    // set up the status light
    pinMode(STATUS_LIGHT_PIN, OUTPUT);

    // set the status light to stay on
    digitalWrite(STATUS_LIGHT_PIN, HIGH);
    m_statusLightWait = floor(STATUS_LIGHT_FREQUENCY_MS / UPDATE_RATE_MS);
    m_statusLightOn = true;

#if ENABLE_CAN
    m_can.startCAN();
    m_can.onMessage<EStopMsg>(MessageID::E_STOP, [this](const EStopMsg& msg) { this->handleEStopMsg(msg); });
    m_can.onMessage<EnableChassisMsg>(MessageID::ENABLE_CHASSIS, [this](const EnableChassisMsg& msg) { this->handleEnableChassisMsg(msg); });
    m_can.onMessage<DrivePowerMsg>(MessageID::DRIVE_POWER, [this](const DrivePowerMsg& msg) { this->handleDrivePowerMsg(msg); });
#endif
}

void Chassis::blinkStatusLight()
{
    // blink the status light every STATUS_LIGHT_FREQUENCY_MS
    if (m_statusLightWait <= 0)
    {
        if (m_statusLightOn)
        {
            digitalWrite(STATUS_LIGHT_PIN, LOW);
            m_statusLightOn = false;
        }
        else
        {
            digitalWrite(STATUS_LIGHT_PIN, HIGH);
            m_statusLightOn = true;
        }
        m_statusLightWait = floor(STATUS_LIGHT_FREQUENCY_MS / UPDATE_RATE_MS);
    }
    else
    {
        m_statusLightWait--;
    }
}

void Chassis::updateSubsystems(int timeInterval_ms)
{
    if (!m_disabled)
    {
        blinkStatusLight();
#if ENABLE_DRIVEBASE
#if ENABLE_ENCODER
        m_drive_base.updateRPM();
#endif
#endif

    }
    else
    {
#if ENABLE_SERIAL
        digitalWrite(STATUS_LIGHT_PIN, HIGH);
        Serial.println("DISABLED");
#endif
    }

    // Send the status message
    m_can.send(StatusMsg{.source=SubSystemID::CHASSIS, .estopped = m_disabled, .enabled = !m_disabled}, MessageID::TEENSY_STATUS);
}

void Chassis::runBackgroundProcess()
{
#if ENABLE_CAN
    m_can.poll();
#endif
}

#if ENABLE_DRIVEBASE
void Chassis::drive(float left_axis, float right_axis)
{
    if (!m_disabled)
    {
        m_drive_base.drive(left_axis, right_axis);
    }
}
#endif

void Chassis::disable()
{
    // disable the rover and stop everything
    m_disabled = true;

    // set the led to solid
    digitalWrite(STATUS_LIGHT_PIN, HIGH);

#if ENABLE_DRIVEBASE
    m_drive_base.forceStop();
#endif
}

bool Chassis::isDisabled()
{
    return m_disabled;
}

// CAN handlers
void Chassis::handleEStopMsg(const EStopMsg &msg)
{
    this->disable();
}

void Chassis::handleEnableChassisMsg(const EnableChassisMsg &msg)
{
    if (msg.enable == 1) {
        m_disabled = false;
    } else {
        this->disable();
    }
}

void Chassis::handleDrivePowerMsg(const DrivePowerMsg &msg)
{
    if (!m_disabled)
    {
        m_drive_base.drive(msg.left_power, msg.right_power);
        Serial.printf("left %f", msg.left_power);
        Serial.printf("right %f", msg.right_power);
    }
}
