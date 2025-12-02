#pragma once

#include <cstdint>
#include <array>
#include <cstring>

#include "CAN/message_types.h"
#include "can_frame.h"

template <typename T>
CANFrame encode(const T &msg, MessageType msg_type) {
    CANFrame frame {};
    frame.id = static_cast<uint32_t>(msg_type);
    frame.dlc = sizeof(T);
    memcpy(frame.data, &msg, sizeof(T));
}

template <typename T>
T decode(const CANFrame &frame) {
    T msg{};
    memcpy(&msg, frame.data, sizeof(T));
    return msg;
}
