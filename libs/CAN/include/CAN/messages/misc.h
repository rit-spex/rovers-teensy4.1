#pragma once

#include "misc_codec.h"
#include "CAN/codec.h"

#include <cstdint>

static constexpr uint8_t E_STOP_DLC = 5;
static constexpr uint8_t HEARTBEAT_DLC = 5;

enum class EStopSource : uint8_t {
    ROS = 0,
    ARM = 1,
    CHASSIS = 2,
    SCIENCE = 3,
};

struct EStopMsg {
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

struct HeartbeatMsg {
    HeartbeatStatus status; // 1 byte
    uint32_t uptime_ms; // 4 bytes
};
