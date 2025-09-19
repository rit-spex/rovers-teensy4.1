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

#if ENABLE_CAN
Chassis::Chassis(unsigned long* currentCycle)
    :m_can(currentCycle), m_currentCyclePtr(currentCycle) {
}
#else
Chassis::Chassis(unsigned long* currentCycle)
    : m_currentCyclePtr(currentCycle) {
}
#endif

Chassis::~Chassis() {}

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
#endif
}

void Chassis::BlinkStatusLight()
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
#if ENABLE_CAN
        m_disabled = m_can.getUnpackedMessage(CAN::Message_ID::E_STOP, 0);
#endif

    }
    if (!m_disabled)
    {
        // m_disabled = (*m_currentCyclePtr - m_can.m_lastRecievedMsgCycle > 25) && m_can.m_recievedMsg;
        // Serial.println(m_can.m_lastRecievedMsgCycle);
        // Serial.println(m_can.m_recievedMsg);
    }
    if (!m_disabled)
    {
        BlinkStatusLight();
#if ENABLE_DRIVEBASE
#if ENABLE_ENCODER
        m_drive_base.updateRPM();
#else
#if ENABLE_CAN
        // Serial.println(m_can.getUnpackedMessage(CAN::Message_ID::DRIVE_POWER, 0));
        float leftPower = ((float)m_can.getUnpackedMessage(CAN::Message_ID::DRIVE_POWER, 0) - 100.0) / 100;
        float rightPower = ((float)m_can.getUnpackedMessage(CAN::Message_ID::DRIVE_POWER, 1) - 100.0) / 100;

        //Serial.println("\n\nABOUT TO DRIVE\n\n");

        Serial.printf("left_power: %d\n", leftPower);
        Serial.printf("right_power: %d\n", rightPower);

        m_drive_base.drive(leftPower, rightPower);
#endif

#endif

#endif

#if ENABLE_TEMP
        m_temp_subsystem.updateFans();
#endif
    }
    else
    {
#if ENABLE_SERIAL
        digitalWrite(STATUS_LIGHT_PIN, HIGH);
        Serial.println("DISABLED");
#endif
    }
}

void Chassis::runBackgroundProcess()
{
#if ENABLE_CAN
    m_can.readMsgBuffer();
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
