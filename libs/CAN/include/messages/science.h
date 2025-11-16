#pragma once

#include "../encoding.h"
#include <cstdint>

static constexpr uint8_t ENABLE_SCIENCE_DLC = 1;
static constexpr uint8_t MOVE_AUGER_DLC = 8;
static constexpr uint8_t HOME_AUGER_DLC = 0;
static constexpr uint8_t ENABLE_DRILL_DLC = 1;
static constexpr uint8_t MOVE_SLIDE_DLC = 1;

struct EnableScienceMsg {
    Bool2 enable;
};

template <>
inline CANFrame encode<EnableScienceMsg>(const EnableScienceMsg &m) {
    CANFrame frame{};
    frame.id = static_cast<uint32_t>(MessageType::ENABLE_SCIENCE);
    frame.dlc = ENABLE_SCIENCE_DLC;

    frame.data[0] = pack_bool_2(m.enable);

    return frame;
}

template <>
inline EnableScienceMsg decode<EnableScienceMsg>(const CANFrame &f) {
    EnableScienceMsg m;
    uint8_t enable_val = f.data[0] & 0b11;

    switch (enable_val) {
        case 0b01: m.enable = Bool2::Off; break;
        case 0b10: m.enable = Bool2::On; break;
        default: m.enable = Bool2::Invalid; break;
    }

    return m;
}

enum class ScienceState : uint8_t {
    Active = 0,
    Stop = 1,
};

enum class ScienceDir : uint8_t {
    Reverse = 0,
    Forward = 1,
};

struct MoveAugerMsg {
    ScienceState state;
    ScienceDir direction;
};

template <>
inline CANFrame encode<MoveAugerMsg>(const MoveAugerMsg &m) {
    CANFrame frame{};
    frame.id = static_cast<uint32_t>(MessageType::MOVE_AUGER);
    frame.dlc = MOVE_AUGER_DLC;

    frame.data[0] = static_cast<uint8_t>(m.state);
    frame.data[1] = static_cast<uint8_t>(m.direction);

    for (int i = 2; i < MOVE_AUGER_DLC; ++i) {
        frame.data[i] = 0;
    }

    return frame;
}

template <>
inline MoveAugerMsg decode<MoveAugerMsg>(const CANFrame &f) {
    MoveAugerMsg m;
    m.state = static_cast<ScienceState>(f.data[0] & 0x01);
    m.direction = static_cast<ScienceDir>(f.data[1] & 0x01);

    return m;
}

struct HomeAugerMsg {

};

template <>
inline CANFrame encode<HomeAugerMsg>(const HomeAugerMsg &m) {
    CANFrame frame{};
    frame.id = static_cast<uint32_t>(MessageType::HOME_AUGER);
    frame.dlc = HOME_AUGER_DLC;

    return frame;
}

template <>
inline HomeAugerMsg decode<HomeAugerMsg>(const CANFrame &f) {
    HomeAugerMsg m;
    return m;
}

struct EnableDrillMsg {
    Bool2 enable;
};

template <>
inline CANFrame encode<EnableDrillMsg>(const EnableDrillMsg &m) {
    CANFrame frame{};
    frame.id = static_cast<uint32_t>(MessageType::ENABLE_DRILL);
    frame.dlc = ENABLE_DRILL_DLC;

    frame.data[0] = pack_bool_2(m.enable);

    return frame;
}

template <>
inline EnableDrillMsg decode<EnableDrillMsg>(const CANFrame &f) {
    EnableDrillMsg m;
    uint8_t enable_val = f.data[0] & 0b11;

    switch (enable_val) {
        case 0b01: m.enable = Bool2::Off; break;
        case 0b10: m.enable = Bool2::On; break;
        default: m.enable = Bool2::Invalid; break;
    }

    return m;
}

// XXX: so ik this needs to be defined for the CAN library so ROS can have the
// types, but i have fears about desync between this and the teensy science code
// so i wonder if theres a way for them to share the enum.
// For now just going to update them identically
enum class SlidePosition : uint8_t {
    Home = 0x00,
    OpenSample = 0x01,
    SampleCache = 0x02,
    MiddleContainer = 0x03,
    EndSample = 0x04,
};

struct MoveSlideMsg {
    SlidePosition position;
};

template <>
inline CANFrame encode<MoveSlideMsg>(const MoveSlideMsg &m) {
    CANFrame frame{};
    frame.id = static_cast<uint32_t>(MessageType::MOVE_SLIDE);
    frame.dlc = MOVE_SLIDE_DLC;

    frame.data[0] = static_cast<uint8_t>(m.position);

    return frame;
}

template <>
inline MoveSlideMsg decode<MoveSlideMsg>(const CANFrame &f) {
    MoveSlideMsg m;
    m.position = static_cast<SlidePosition>(f.data[0]);

    return m;
}

