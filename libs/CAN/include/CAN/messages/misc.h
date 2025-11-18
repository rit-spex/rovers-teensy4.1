#pragma once

#include "misc_codec.h"
#include "CAN/codec.h"

#include <cstdint>

static constexpr uint8_t E_STOP_DLC = 0;
static constexpr uint8_t HEARTBEAT_DLC = 0;


struct EStopMsg {
};

struct HeartbeatMsg {
};
