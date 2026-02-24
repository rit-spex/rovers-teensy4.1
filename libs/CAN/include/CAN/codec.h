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

// SPECIAL ARM ENCODING AND DECODING
const uint32_t OPC_ENABLE_POS_MODE = 0x6040;
const uint32_t OPC_SEND_POS = 0x607a;
const uint32_t OPC_GET_POS = 0x6064;

const uint32_t DEVICE_ID_OFFSET_SEND = 0x600;
const uint32_t DEVICE_ID_OFFSET_RECV = 0x580;

const uint32_t RECV_READ_BACK_ONE = 0x4F;
const uint32_t RECV_READ_BACK_TWO = 0x4B;
const uint32_t RECV_READ_BACK_FOUR = 0x43;

CANMessage buildArmMsg(int deviceIdx, uint32_t operationCode, uint64_t data,
                       int length, int idCode);

#endif // SPEX_CAN_CODEC_H
