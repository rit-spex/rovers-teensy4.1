// Auto-generated encode/decode for ../../include/messages/heartbeat.h
#pragma once

#include "../../include/messages/heartbeat.h"   // struct definitions


// ---------------- Auto-generated encode/decode ----------------





template <>
inline CANFrame encode<HeartbeatMsg>(const HeartbeatMsg &m) {
    CANFrame frame{};
    frame.id = static_cast<uint32_t>(MessageType::HEARTBEAT);
    frame.dlc = HEARTBEAT_DLC;


    frame.data[0] = static_cast<uint8_t>(m.timestamp);


    return frame;
}

template <>
inline HeartbeatMsg decode<HeartbeatMsg>(const CANFrame &f) {
    HeartbeatMsg m;

    m.timestamp = static_cast<uint32_t>(f.data[0]);

    return m;
}
