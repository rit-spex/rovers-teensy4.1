// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : ACAN_T4.cpp
// purpose      : to simulate the canbus file
// created on   : 7/23/2025 - Tyler
// last modified: 7/23/2025 - Tyler
// --------------------------------------------------------------------

#include <ACAN_T4.h>

// ACAN_T4_Settings
ACAN_T4_Settings::ACAN_T4_Settings(int baudrate)
{
    std::cout << "ACAN_T4 Settings: baudrate:" << baudrate << std::endl;
}

// CANbus
CANbus::CANbus()
{
    
}

void CANbus::begin(ACAN_T4_Settings acan_t4_settings)
{
    std::cout << "CANbus begin called with settings: " << std::endl;
}

bool CANbus::receive(CANMessage message)
{
    std::cout << "CANbus receive called with message: " << std::endl;

    return true;
}

void CANbus::tryToSend(CANMessage message)
{
    std::cout << "CANbus tryToSend called with message: " << std::endl;
}