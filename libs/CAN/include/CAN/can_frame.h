#pragma once

#include <array>
#include <cstdint>

struct CANFrame {
    uint32_t id;
    uint8_t dlc;
    std::array<uint8_t, 8> data;
};
