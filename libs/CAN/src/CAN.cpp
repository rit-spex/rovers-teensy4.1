#include "CAN/CAN.h"

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

#include "CAN/message_id.h"
#include <cstdint>
#include <stdexcept>
#define ENABLE_SERIAL 1

bool tryToSendAll(const CANMessage &frame)
{

    if (CAN::CAN_MODE::CAN1 == ActiveCAN)
    {
        return ACAN_T4::can1.tryToSend(frame);
    }
    else if (CAN::CAN_MODE::CAN2 == ActiveCAN)
    {
        return ACAN_T4::can2.tryToSend(frame);
    }
    else if (CAN::CAN_MODE::CAN3 == ActiveCAN)
    {
        return ACAN_T4::can3.tryToSend(frame);
    }
}

void CAN::startCAN()
{
    // Set the settings to the CAN
    ACAN_T4_Settings settings(CAN_BAUDRATE);
    // XXX: recently changed could be source of issues in the future
    settings.mTxPinIsOpenCollector = false;
    settings.mRxPinConfiguration = ACAN_T4_Settings::NO_PULLUP_NO_PULLDOWN;

    // Start the CAN bus based on ActiveCAN
    if (CAN::CAN_MODE::CAN1 == ActiveCAN)
    {
        ACAN_T4::can1.begin(settings); //, &primaryFilter, 1) ;
    }
    else if (CAN::CAN_MODE::CAN2 == ActiveCAN)
    {
        ACAN_T4::can2.begin(settings); //, &primaryFilter, 1) ;
    }
    else if (CAN::CAN_MODE::CAN3 == ActiveCAN)
    {
        ACAN_T4::can3.begin(settings); //, &primaryFilter, 1) ;
    }

#if ENABLE_SERIAL
    Serial.println("CAN StartUp");
#endif
}

void CAN::poll()
{
    CANMessage frame;
    bool received = false;

    if (CAN::CAN_MODE::CAN1 == ActiveCAN)
    {
        received = ACAN_T4::can1.receive(frame);
    }
    else if (CAN::CAN_MODE::CAN2 == ActiveCAN)
    {
        received = ACAN_T4::can2.receive(frame);
    }
    else if (CAN::CAN_MODE::CAN3 == ActiveCAN)
    {
        received = ACAN_T4::can3.receive(frame);
    }

    if (received)
    {
        dispatch(frame);
        Serial.println("received frame");
    }
}

// void CAN::armPoll() {
//     CANMessage frame;
//     bool received = false;

//     if (CAN::CAN_MODE::CAN1 == ActiveCAN)
//     {
//         received = ACAN_T4::can1.receive(frame);
//     }
//     else if (CAN::CAN_MODE::CAN2 == ActiveCAN)
//     {
//         received = ACAN_T4::can2.receive(frame);
//     }
//     else if (CAN::CAN_MODE::CAN3 == ActiveCAN)
//     {
//         received = ACAN_T4::can3.receive(frame);
//     }

//     if (received)
//     {
//         if ((frame.id - DEVICE_ID_OFFSET_RECV) > 0 && (frame.id - DEVICE_ID_OFFSET_RECV < 10)) {
//             if (frame.data[0] == RECV_READ_BACK_FOUR) {
//                 if ((frame.data[1] == ((OPC_GET_POS >> 0) & 0xff)) && (frame.data[2] == ((OPC_GET_POS >> 8) & 0xff))) {
//                     Serial.printf("Device: %d", frame.id - 0x580);
//                     Serial.printf("Pos: %d", frame.data[1]);
//                     Serial.println();
//                 }
//             }
//         }
//     }
// }

void CAN::dispatch(CANMessage &frame)
{
    MessageID id = static_cast<MessageID>(frame.id);
    // Attempts to locate `id` as a key in `m_dispatcher`
    auto it = m_dispatcher.find(id);
    // If `m_dispatcher` contains `id`
    if (it != m_dispatcher.end())
    {
        // Calls the corresponding function with the CAN frame as an argument.
        it->second(frame);
    }
}
