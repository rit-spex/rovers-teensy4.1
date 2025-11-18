// Auto-generated encode/decode for ../../include/messages/estop.h
#pragma once

#include "../../include/messages/estop.h"   // struct definitions


// ---------------- Auto-generated encode/decode ----------------





template <>
inline CANFrame encode<EStopMsg>(const EStopMsg &m) {
    CANFrame frame{};
    frame.id = static_cast<uint32_t>(MessageType::E_STOP);
    frame.dlc = E_STOP_DLC;



    return frame;
}

template <>
inline EStopMsg decode<EStopMsg>(const CANFrame &f) {
    EStopMsg m;

    return m;
}
