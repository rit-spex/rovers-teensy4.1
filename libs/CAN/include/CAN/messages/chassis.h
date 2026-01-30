// ============================================================================
// File: chassis.h
//
// Authors:
//     - Lucas Newcomb (@pants721)
//
// Description:
//     Provides the types for CAN messages related the Chassis subsystem.
// Note:
//     Message structs MUST have `__attribute__((packed))` in order to avoid
//     the compiler inserting padding, which would make our encoding and
//     decoding compiler dependent which is a big no-no.
// ============================================================================

#ifndef SPEX_CAN_MESSAGES_CHASSIS_H
#define SPEX_CAN_MESSAGES_CHASSIS_H

#include <cstdint>

struct __attribute__((packed)) EnableChassisMsg
{
    uint8_t enable;
};

struct __attribute__((packed)) DrivePowerMsg
{
    float left;
    float right;
};

#endif // SPEX_CAN_MESSAGES_CHASSIS_H
