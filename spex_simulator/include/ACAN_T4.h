// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : ACAN_T4.h
// purpose      : to simulate the canbus file
// created on   : 7/23/2025 - Tyler
// last modified: 7/23/2025 - Tyler
// --------------------------------------------------------------------

#ifndef ACAN_T4_H
#define ACAN_T4_H

#include <cstdint>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <vector>

#define RECV_PORT 8000
#define UDP_IP "127.0.0.1"
#define SEND_PORT 8001
#define UDP_BUF_SIZE 1024

// # of uint8s that each part of the CAN message should take when converted to
// UDP packet
#define ID_LEN 4
#define DLC_LEN 1

struct CANMessage
{
    uint32_t id;
    uint8_t data[8];
    uint8_t len;
};

class ACAN_T4_Settings
{
public:
    static const int NO_PULLUP_NO_PULLDOWN = 1;

    ACAN_T4_Settings(int baudrate);
    bool mTxPinIsOpenCollector;
    int mRxPinConfiguration;
};

class CANbus
{
public:
    CANbus(void);
    void begin(ACAN_T4_Settings acan_t4_settings);
    bool receive(CANMessage &message);
    bool tryToSend(CANMessage message);

private:
    int m_sock = -1;
    uint16_t m_port;
    std::string m_ip;
    sockaddr_in m_dest{};
    int m_sendPort;
};

class ACAN_T4
{
public:
    static CANbus can1;
    static CANbus can2;
    static CANbus can3;
};

#endif
