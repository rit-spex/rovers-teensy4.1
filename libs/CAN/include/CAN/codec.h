#pragma once

#include <cstdint>
#include <array>

#include "can_frame.h"

template <typename T>
CANFrame encode(const T &msg);

template <typename T>
T decode(const CANFrame &frame);
