// ============================================================================
// File: codec.h
//
// Authors:
//     - Lucas Newcomb (@pants721)
//
// Description:
//     Provides the `MessageID` enum which our CAN messages use as identifiers.
// ============================================================================

#ifndef SPEX_CAN_MESSAGE_ID_H
#define SPEX_CAN_MESSAGE_ID_H

#include <cstdint>

enum class MessageID : uint32_t
{
    E_STOP = (uint32_t)0,
    ROS_HEARTBEAT = (uint32_t)1,
    TEENSY_STATUS = (uint32_t)2,

    // chassis
    ENABLE_CHASSIS = (uint32_t)10,
    TARGET_RPM = (uint32_t)11,
    DRIVE_POWER = (uint32_t)13,

    // arm
    ENABLE_ARM = (uint32_t)20,
    MOVE_BASE = (uint32_t)21,
    MOVE_SHOULDER = (uint32_t)22,
    MOVE_ELBOW = (uint32_t)23,
    BEND_WRIST = (uint32_t)24,
    TWIST_WRIST = (uint32_t)25,
    MOVE_CLAW = (uint32_t)26,
    MOVE_SOLENOID = (uint32_t)27,
    BASE_POS = (uint32_t)28,

    ARM_STATUS = (uint32_t)30,

    // science
    ENABLE_SCIENCE = (uint32_t)40,
    MOVE_AUGER = (uint32_t)41,
    HOME_AUGER = (uint32_t)42,
    ENABLE_DRILL = (uint32_t)43,
    MOVE_SLIDE = (uint32_t)44,
};

#endif // SPEX_CAN_MESSAGE_ID_H
