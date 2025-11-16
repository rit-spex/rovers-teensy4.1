#pragma once

#include "../encoding.h"
#include <cstdint>

static constexpr uint8_t HEARTBEAT_DLC = 4;

struct HeartbeatMsg {
    uint32_t timestamp;
};

template <>
inline CANFrame encode<HeartbeatMsg>(const HeartbeatMsg &m) {
    CANFrame frame{};
    frame.id = static_cast<uint32_t>(MessageType::HEARTBEAT);
    frame.dlc = HEARTBEAT_DLC;

    frame.data[0] = (m.timestamp >> 24) & 0xFF;
    frame.data[1] = (m.timestamp >> 16) & 0xFF;
    frame.data[2] = (m.timestamp >> 8) & 0xFF;
    frame.data[3] = (m.timestamp >> 0) & 0xFF;

    return frame;
}

template <>
inline HeartbeatMsg decode<HeartbeatMsg>(const CANFrame &f) {
    HeartbeatMsg m;
    m.timestamp =
        (uint32_t(f.data[0]) << 24) |
        (uint32_t(f.data[1]) << 16) |
        (uint32_t(f.data[2]) <<  8) |
        uint32_t(f.data[2]);

    return m;
}
