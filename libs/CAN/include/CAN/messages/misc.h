#ifndef CAN_MESSAGES_MISC_H
#define CAN_MESSAGES_MISC_H

#include "CAN/codec.h"

#include <cstdint>

enum class EStopSource : uint8_t {
    ROS = 0,
    ARM = 1,
    CHASSIS = 2,
    SCIENCE = 3,
};

struct __attribute__((packed)) EStopMsg {
    EStopSource source; // 1 byte
    uint32_t timestamp_ms; // 4 bytes (uptime)
};

enum class HeartbeatStatus : uint8_t {
    OK = 0,
    DEGRADED = 1,
    ERROR = 2,
    FAULT = 3,
    ESTOP = 4,
    STARTUP = 5,
};

struct __attribute__((packed)) HeartbeatMsg {
    HeartbeatStatus status; // 1 byte
    uint32_t uptime_ms; // 4 bytes
};

#endif // CAN_MESSAGES_MISC_H
