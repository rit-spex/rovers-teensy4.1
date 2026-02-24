// ============================================================================
// File: science.h
//
// Authors:
//     - Lucas Newcomb (@pants721)
//
// Description:
//     Provides the types for CAN messages related to the Science subsystem.
// Note:
//     Message structs MUST have `__attribute__((packed))` in order to avoid
//     the compiler inserting padding, which would make our encoding and
//     decoding compiler dependent which is a big no-no.
// ============================================================================

#ifndef SPEX_CAN_MESSAGES_SCIENCE_H
#define SPEX_CAN_MESSAGES_SCIENCE_H

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
    uint32_t position;
    uint8_t home;
};

struct __attribute__((packed)) EnableDrillMsg
{
    uint8_t enable;
};

// XXX: so ik this needs to be defined for the CAN library so ROS can have the
// types, but i have fears about desync between this and the teensy science code
// so i wonder if theres a way for them to share the enum.
// For now just going to update them identically
enum class SlideStage : uint8_t
{
    Purge = (uint8_t)0,
    Home = (uint8_t)1,
    SampleCache = (uint8_t)2,
    Collection1 = (uint8_t)3,
    Collection2 = (uint8_t)4,
};

struct __attribute__((packed)) MoveSlideMsg
{
    SlideStage stage;
    uint8_t home;
};

struct __attribute__((packed)) EnablePumpMsg
{
    uint8_t id;
    uint8_t enable;
};

enum class InstrumentSlideStage : uint8_t
{
    Site1Pos1 = (uint8_t)0,
    Site1Pos2 = (uint8_t)1,
    Site2Pos1 = (uint8_t)2,
    Site2Pos2 = (uint8_t)3,
};

struct __attribute__((packed)) MoveSpectrometerSlideMsg
{
    InstrumentSlideStage stage;
    uint8_t home;
};

struct __attribute__((packed)) MoveFluorometerSlideMsg
{
    InstrumentSlideStage stage;
    uint8_t home;
};

struct __attribute__((packed)) EnableFluorometerMicroPumpMsg
{
    uint8_t enable;
};

struct __attribute__((packed)) EnablePrimerMsg
{
    uint8_t enable;
};

struct __attribute__((packed)) EnableVibrationMsg
{
    uint8_t enable;
};

// READ MESSAGES

struct __attribute__((packed)) ReadAugerMsg
{
    uint32_t position;
    uint8_t limitSwitch;
};

struct __attribute__((packed)) ReadSlideMsg
{
    SlideStage stage;
    uint32_t position;
    uint8_t limitSwitch;
};

struct __attribute__((packed)) ReadDrillMsg
{
    uint8_t enabled;
};

struct __attribute__((packed)) ReadPumpsMsg
{
    uint8_t pump1Enabled;
    uint8_t pump2Enabled;
    uint8_t pump3Enabled;
    uint8_t pump4Enabled;
};

struct __attribute__((packed)) ReadSpectrometerSlideMsg
{
    InstrumentSlideStage stage;
    uint32_t position;
    uint8_t limitSwitch;
};

struct __attribute__((packed)) ReadFluorometerSlideMsg
{
    InstrumentSlideStage stage;
    uint32_t position;
    uint8_t limitSwitch;
};

struct __attribute__((packed)) ReadSpectrometerLightMsg
{
    float wavelength;
};

struct __attribute__((packed)) ReadFluorometerColorSensorMsg
{
    uint16_t red;
    uint16_t green;
    uint16_t blue;
    uint16_t violet;
};

#endif // SPEX_CAN_MESSAGES_SCIENCE_H
