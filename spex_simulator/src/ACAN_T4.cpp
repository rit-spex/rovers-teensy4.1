// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : ACAN_T4.cpp
// purpose      : to simulate the canbus file
// created on   : 7/23/2025 - Tyler
// last modified: 7/23/2025 - Tyler
// --------------------------------------------------------------------

#include "ACAN_T4.h"

#include "spdlog/spdlog.h"
#include <asm-generic/socket.h>
#include <cstdio>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <poll.h>
#include <vector>

#define UDP_PORT 8000
#define UDP_IP "127.0.0.1"

// ACAN_T4_Settings
ACAN_T4_Settings::ACAN_T4_Settings(int baudrate)
{
    spdlog::debug("ACAN_TF Settings: baudrate: {}", baudrate);
}

// CANbus
CANbus::CANbus()
{
    m_port = UDP_PORT;
    m_ip = UDP_IP;
}

void CANbus::begin(ACAN_T4_Settings acan_t4_settings)
{
    // XXX:
    m_port = UDP_PORT;
    m_ip = UDP_IP;

    spdlog::debug("CANbus.begin called");
    spdlog::info("Opening CAN UDP server on {}:{}", m_ip, m_port);
    m_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (m_sock < 0)
    {
        spdlog::error("Failed to create CAN socket");
        return;
    }

    int yes = 1;
    setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

    int flags = fcntl(m_sock, F_GETFL, 0);
    if (flags < 0 || fcntl(m_sock, F_SETFL, flags | O_NONBLOCK) < 0)
    {
        spdlog::error("Failed to set UDP server to non-blocking");
        return;
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(m_port);

    if (bind(m_sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0)
    {
        spdlog::error("Failed to bind UDP socket");
        return;
    }

    memset(&m_dest, 0, sizeof(m_dest));
    m_dest.sin_family = AF_INET;
    m_dest.sin_port = htons(m_port);
    inet_pton(AF_INET, m_ip.c_str(), &m_dest.sin_addr);
}

bool CANbus::receive(CANMessage message)
{
    std::vector<uint8_t> buf(1024);
    ssize_t len = recv(m_sock, buf.data(), buf.size(), 0);
    if (len <= 0)
    {
        return false;
    }

    memcpy(&message.id, buf.data(), 4);
    message.len = buf[4];
    memcpy(message.data, buf.data() + 5, message.len);
    spdlog::debug("Received message: ID {} LEN {}", message.id, message.len);

    return true;
}

bool CANbus::tryToSend(CANMessage message)
{
    spdlog::debug("CANbus.tryToSend called");
    std::vector<uint8_t> buf(5 + message.len);
    memcpy(buf.data(), &message.id, 4);
    buf[4] = message.len;
    memcpy(buf.data() + 5, message.data, message.len);

    ssize_t sent = sendto(m_sock, buf.data(), buf.size(), 0, (sockaddr*)&m_dest, sizeof(m_dest));

    return sent == (ssize_t)buf.size();
}
