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
#include <arpa/inet.h>
#include <asm-generic/socket.h>
#include <cassert>
#include <cerrno>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <fcntl.h>
#include <netinet/in.h>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

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
    m_sendPort = SEND_PORT;
}

void CANbus::begin(ACAN_T4_Settings acan_t4_settings)
{
    // TODO: CHANGE THIS
    m_port = UDP_PORT;
    m_ip = UDP_IP;
    m_sendPort = SEND_PORT;

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

    if (bind(m_sock, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) < 0)
    {
        spdlog::error("Failed to bind UDP socket");
        return;
    }

    memset(&m_dest, 0, sizeof(m_dest));
    m_dest.sin_family = AF_INET;
    m_dest.sin_port = htons(m_sendPort);
    m_dest.sin_addr.s_addr = inet_addr(m_ip.c_str());
    // inet_pton(AF_INET, m_ip.c_str(), &m_dest.sin_addr);
}

bool CANbus::receive(CANMessage message)
{
    uint8_t buf[1024];
    ssize_t recLen = recv(m_sock, &buf[0], sizeof(buf), 0);
    if (recLen < 5)
    {
        return false;
    }

    message.len = buf[4];

    // Bad length
    if (recLen - 5 != message.len)
    {
        spdlog::error("Received message was of different length than DLC specified");
        return false;
    }

    memcpy(&message.id, buf, 4);
    memcpy(message.data, buf + 5, message.len);
    // TODO: Can probably be a debug log
    spdlog::info("Received message: ID {} LEN {} DATA {}", message.id, message.len,
                 std::string(reinterpret_cast<const char *>(message.data), sizeof(message.data)));

    return true;
}

bool CANbus::tryToSend(CANMessage message)
{
    spdlog::debug("CANbus.tryToSend called");

    if (m_sock < 0)
    {
        spdlog::error("Socket not initialized");
        return false;
    }

    uint8_t buf[5 + message.len];
    uint32_t id = htonl(message.id);
    memcpy(buf, &id, 4);

    buf[4] = message.len;

    memcpy(buf + 5, message.data, message.len);

    ssize_t sent = sendto(m_sock, buf, sizeof(buf), MSG_CONFIRM, (const struct sockaddr *)&m_dest, sizeof(m_dest));

    if (sent < 0)
    {
        spdlog::error("Error sending UDP packet: {}", strerror(errno));
        return false;
    }

    if (sent - 5 != message.len)
    {
        spdlog::error("Sent packet size does not match specified message length: {} != {}", sent - 5, message.len);
    }

    return sent == (ssize_t)sizeof(buf);
}
