// ============================================================================
// File: misc.h
//
// Authors:
//     - Lucas Newcomb (@pants721)
//
// Description:
//     Provides the types for CAN messages shared across multiple subsystems.
// Note:
//     Message structs MUST have `__attribute__((packed))` in order to avoid
//     the compiler inserting padding, which would make our encoding and
//     decoding compiler dependent which is a big no-no.
// ============================================================================

#ifndef SPEX_CAN_MESSAGES_MISC_H
#define SPEX_CAN_MESSAGES_MISC_H

#include "CAN/codec.h"

#include <cstdint>

enum class SubSystemID: uint8_t
{
    ROS = 0,
    ARM = 1,
    CHASSIS = 2,
    SCIENCE = 3,
};

// Indicates that all subsystems should stop immediately and shutdown.
// `source` indicates the subsystem that sent out the message initially. This
// is useful for understanding the origin of the error and would hopefully be
// captured by ROS logs.
struct __attribute__((packed)) EStopMsg
{
    SubSystemID source;    // 1 byte
    uint32_t timestamp_ms; // 4 bytes (uptime)
};

// Sent out periodically between the ROS and each subsystem in order to ensure
// both are still operational.
// If a subsystem does not get a hearbeat from the ROS, it should shut down all
// motors as we've lost control of them (2025 tyler rover wrestling incident)
// (those who know).
// If ROS doesn't receieve a heartbeat from a subsystem, that also indicates
// an error and should be handled.
struct __attribute__((packed)) HeartbeatMsg
{
    SubSystemID source;
    uint32_t uptime_ms; // timestamp since startup
    uint8_t enabled;
};

#endif // SPEX_CAN_MESSAGES_MISC_H
