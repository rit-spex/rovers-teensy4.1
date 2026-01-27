// ============================================================================
// File: codec.h
//
// Authors:
//     - Lucas Newcomb (@pants721)
//
// Description:
//     Provides template functions for encoding and decoding CAN message structs.
//     Uses `memcpy` and `sizeof`, which should work for all current and future
//     structs, given their data can be serialized as integers.
// ============================================================================

#ifndef SPEX_CAN_CODEC_H
#define SPEX_CAN_CODEC_H

// PIO test framework can't use ACAN_T4 if we're testing on native (not teensy)
// which is the case for testing the encoding and decoding testing
#ifdef CAN_CODEC_TEST
struct CANMessage {
    uint32_t id;
    uint8_t len;
    uint8_t data[8];
};
#else
#include <ACAN_T4.h>
#endif

#include <array>
#include <cstdint>
#include <cstring>

#include "CAN/message_id.h"

template <typename T>
CANMessage encode(const T &msg, MessageID msg_id)
{
    CANMessage frame{};
    frame.id = static_cast<uint32_t>(msg_id);
    frame.len = sizeof(T);
    memcpy(frame.data, &msg, sizeof(T));

    return frame;
}

template <typename T>
T decode(const CANMessage &frame)
{
    T msg{};
    memcpy(&msg, frame.data, sizeof(T));
    return msg;
}

#endif // SPEX_CAN_CODEC_H
