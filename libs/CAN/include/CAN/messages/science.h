#ifndef CAN_MESSAGES_SCIENCE_H
#define CAN_MESSAGES_SCIENCE_H

#include "CAN/codec.h"

#include <cstdint>

struct __attribute__((packed)) EnableScienceMsg
{
    uint8_t enable;
};

enum class ScienceState : uint8_t
{
    Active = 0,
    Stop = 1,
};

enum class ScienceDir : uint8_t
{
    Reverse = 0,
    Forward = 1,
};

struct __attribute__((packed)) MoveAugerMsg
{
    ScienceState state;
    ScienceDir direction;
};

struct __attribute__((packed)) HomeAugerMsg
{
};

struct __attribute__((packed)) EnableDrillMsg
{
    uint8_t enable;
};

// XXX: so ik this needs to be defined for the CAN library so ROS can have the
// types, but i have fears about desync between this and the teensy science code
// so i wonder if theres a way for them to share the enum.
// For now just going to update them identically
enum class SlidePosition : uint8_t
{
    Home = 0x00,
    OpenSample = 0x01,
    SampleCache = 0x02,
    MiddleContainer = 0x03,
    EndSample = 0x04,
};

struct __attribute__((packed)) MoveSlideMsg
{
    SlidePosition position;
};

#endif // CAN_MESSAGES_SCIENCE_H
