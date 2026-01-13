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

    // science
    ENABLE_SCIENCE = (uint32_t)30,
    MOVE_AUGER = (uint32_t)31,
    HOME_AUGER = (uint32_t)32,
    ENABLE_DRILL = (uint32_t)33,
    MOVE_SLIDE = (uint32_t)34,
};

#endif // SPEX_CAN_MESSAGE_ID_H
