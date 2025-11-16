#pragma once

#include "../encoding.h"
#include <cstdint>

static constexpr uint8_t E_STOP_DLC = 0;

struct EStopMsg {

};

template <>
inline CANFrame encode<EStopMsg>(const EStopMsg &m) {
    CANFrame frame{};
    frame.id = static_cast<uint32_t>(MessageType::E_STOP);
    frame.dlc = E_STOP_DLC;

    return frame;
}

template<>
inline EStopMsg decode<EStopMsg>(const CANFrame &f) {
    EStopMsg m;

    return m;
}
