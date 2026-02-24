// ============================================================================
// File: arm.h
//
// Authors:
//     - Lucas Newcomb (@pants721)
//
// Description:
//     Provides the types for CAN messages related the Arm subsystem.
// Note:
//     Message structs MUST have `__attribute__((packed))` in order to avoid
//     the compiler inserting padding, which would make our encoding and
//     decoding compiler dependent which is a big no-no.
// ============================================================================

#ifndef SPEX_CAN_MESSAGES_ARM_H
#define SPEX_CAN_MESSAGES_ARM_H

#include "CAN/codec.h"

#include <cstdint>

struct __attribute__((packed)) EnableArmMsg
{
    uint8_t enable;
};

// ARM COMMANDS

enum class ArmState : uint8_t
{
    Active = 0,
    Stop = 1,
};

enum class ArmDir : uint8_t
{
    Reverse = 0,
    Forward = 1,
};

// struct __attribute__((packed)) MoveBaseMsg
// {
//     ArmState state;
//     ArmDir direction;
// };

// struct __attribute__((packed)) MoveShoulderMsg
// {
//     ArmState state;
//     ArmDir direction;
// };

// struct __attribute__((packed)) MoveElbowMsg
// {
//     ArmState state;
//     ArmDir direction;
// };

struct __attribute__((packed)) BendWristMsg
{
    float position;
};

struct __attribute__((packed)) TwistWristMsg
{
    float position;
};

struct __attribute__((packed)) MoveClawMsg
{
    float position;
};

struct __attribute__((packed)) MoveSolenoidMsg
{
    ArmState state;
    ArmDir direction;
};




// struct __attribute__((packed)) ReadBaseMsg
// {
//     float position;
// };

// struct __attribute__((packed)) ReadShoulderMsg
// {
//     float position;
// };

// struct __attribute__((packed)) ReadElbowMsg
// {
//     float position;
// };


struct __attribute__((packed)) ReadBendMsg
{
    float position;
};

struct __attribute__((packed)) ReadTwistMsg
{
    float position;
};

struct __attribute__((packed)) ReadClawMsg
{
    float position;
};



#endif // SPEX_CAN_MESSAGES_ARM_H
