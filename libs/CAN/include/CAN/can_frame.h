#pragma once

#include <array>
#include <cstdint>

// XXX: CERTAINLY CONSIDER REPLACING THIS WITH ACAN_T4'S CANMessage (basically
// identical)
struct CANFrame {
    uint32_t id;
    uint8_t dlc;
    std::array<uint8_t, 8> data;
};
