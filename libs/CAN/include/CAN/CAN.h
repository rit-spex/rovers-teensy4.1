#ifndef SPEX_CAN_H
#define SPEX_CAN_H

// Constants
#include <functional>
#define ActiveCAN CAN::CAN_MODE::CAN2
#define CAN_BAUDRATE 500000
#define MSG_LENGTH 8

#include <ACAN_T4.h>
#include <Arduino.h>
#include <stdint.h>
#include <unordered_map>

// exports
#include "message_id.h"
#include "codec.h"

// message structs
#include "messages/arm.h"
#include "messages/science.h"
#include "messages/misc.h"


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

    // start the CAN only call this once
    void startCAN();

    template<typename T>
    bool send(const T &msg, MessageID msg_id) {
        CANMessage frame = encode(msg, msg_id);
        return tryToSendAll(frame);
    }

    template <typename T>
    void onMessage(MessageID msg_id, std::function<void(const T &)> callback) {
        auto wrapper = [callback](const CANMessage &frame) {
            T msg = decode<T>(frame);
            callback(msg);
        };
        m_dispatcher[msg_id] = wrapper;
    }

    void poll();
    void dispatch(CANMessage &frame);
private:
    std::unordered_map<MessageID, std::function<void(const CANMessage &)>> m_dispatcher;
};
#endif
