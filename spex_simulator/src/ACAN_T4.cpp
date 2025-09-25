// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : ACAN_T4.cpp
// purpose      : to simulate the canbus file
// created on   : 7/23/2025 - Tyler
// last modified: 7/23/2025 - Tyler
// --------------------------------------------------------------------

#include "spdlog/spdlog.h"
#include <ACAN_T4.h>

// ACAN_T4_Settings
ACAN_T4_Settings::ACAN_T4_Settings(int baudrate)
{
    spdlog::debug("ACAN_TF Settings: baudrate: {}", baudrate);
}

// CANbus
CANbus::CANbus()
{
}

void CANbus::begin(ACAN_T4_Settings acan_t4_settings)
{
    spdlog::debug("CANbus.begin called with settings: ");
}

bool CANbus::receive(CANMessage message)
{
    // enter default data
    message.id = 0;
    message.len = 0;
    for (int byteIdx = 0; byteIdx < 8; byteIdx++)
    {
        message.data[byteIdx] = 0;
    }

    // // print what is returned
    // spdlog::debug("CANbus.receive called with message id: {} len: {}", message.id, message.len);
    //
    // // start of payload
    // std::cout << "data: [";
    //
    // // print each byte
    // for(int byteIdx = 0; byteIdx<message.len; byteIdx++)
    // {
    //     std::cout << "";
    // }
    //
    // // end of payload
    // std::cout << "]" <<std::endl;

    return false;
}

void CANbus::tryToSend(CANMessage message)
{
    // spdlog::debug("CANbus.tryToSend called with message: ");
}
