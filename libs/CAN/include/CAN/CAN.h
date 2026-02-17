// ============================================================================
// File: CAN.h
//
// Authors:
//     - Tyler (@coolly1)
//     - Lucas Newcomb (@pants721)
//
// Description:
//     Provides a wrapper API around the ACAN_T4 library for the rover's CAN
//     messaging.
// ============================================================================

#ifndef SPEX_CAN_H
#define SPEX_CAN_H

// Constants
#include <functional>
#define ActiveCAN CAN::CAN_MODE::CAN2
#define CAN_BAUDRATE 1000000
#define MSG_LENGTH 8

// PIO test framework can't use ACAN_T4 if we're testing on native (not teensy)
// which is the case for testing the encoding and decoding testing
#ifdef CAN_CODEC_TEST
struct CANMessage {
    uint32_t id;
    uint8_t len;
    uint8_t data[8];
}
#else
#include <ACAN_T4.h>
#endif

#include <Arduino.h>
#include <stdint.h>
#include <unordered_map>

// exports
#include "codec.h"
#include "message_id.h"

// message structs
#include "messages/arm.h"
#include "messages/misc.h"
#include "messages/science.h"
#include "messages/chassis.h"

// Tries to send message to all CAN buses
bool tryToSendAll(const CANMessage &frame);

class CAN
{
public:
    typedef enum
    {
        CAN1, // this is pins CRX1 and CTX1
        CAN2, // this is pins CRX2 and CTX2
        CAN3  // this is pins CRX3 and CTX3
    } CAN_MODE;

    CAN() : m_dispatcher() {};

    // start the CAN only call this once
    void startCAN();

    template <typename T>
    bool send(const T &msg, MessageID msg_id)
    {
        CANMessage frame = encode(msg, msg_id);
        return tryToSendAll(frame);
    }

    // Binds a callback function to a message struct `T`.
    // Handles decoding CAN frames into `T` internally.
    template <typename T>
    void onMessage(MessageID msg_id, std::function<void(const T &)> callback)
    {
        auto wrapper = [callback](const CANMessage &frame) {
            T msg = decode<T>(frame);
            callback(msg);
        };
        m_dispatcher[msg_id] = wrapper;
    }

    // Checks for new CAN messages and handle them
    void poll();
    // Given a CAN frame, calls its registered callback function.
    void dispatch(CANMessage &frame);

private:
    // A map storing CAN message IDs and their corresponding callback functions.
    std::unordered_map<MessageID, std::function<void(const CANMessage &)>> m_dispatcher;
};
#endif
