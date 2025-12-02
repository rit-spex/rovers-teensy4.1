#ifndef CAN_CODEC_H
#define CAN_CODEC_H

#include <cstdint>
#include <array>
#include <cstring>
#include <ACAN_T4.h>

#include "CAN/message_types.h"

template <typename T>
CANMessage encode(const T &msg, MessageType msg_type) {
    CANMessage frame {};
    frame.id = static_cast<uint32_t>(msg_type);
    frame.len = sizeof(T);
    memcpy(frame.data, &msg, sizeof(T));
}

template <typename T>
T decode(const CANMessage &frame) {
    T msg{};
    memcpy(&msg, frame.data, sizeof(T));
    return msg;
}

#endif // CAN_CODEC_H
