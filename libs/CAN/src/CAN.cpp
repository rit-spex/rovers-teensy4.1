#include "CAN/CAN.h"
#include "ACAN_T4.h"
#include "CAN/message_types.h"
#include <cstdint>
#include <stdexcept>
#define ENABLE_SERIAL 1

bool tryToSendAll(const CANMessage &frame) {
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
    settings.mTxPinIsOpenCollector = true;
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


void CAN::poll() {
    CANMessage frame;
    bool received = false;

    if (CAN::CAN_MODE::CAN1 == ActiveCAN) {
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

    if (received) {
        dispatch(frame);
    }
}

void CAN::dispatch(CANMessage &frame) {
    MessageType type = static_cast<MessageType>(frame.id);
    auto it = m_dispatcher.find(type);
    if (it != m_dispatcher.end()) {
        it->second(frame);
    }
}
