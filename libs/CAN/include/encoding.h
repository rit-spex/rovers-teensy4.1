#include <cstdint>
#include <array>

struct CANFrame {
    uint32_t id;
    uint8_t dlc;
    std::array<int, 8> data;
};

// two bit boolean type for redundancy
enum class Bool2: uint8_t {
    Off = 0b01,
    On = 0b10,
    Invalid = 0b00,
};

inline uint8_t pack_bool_2(Bool2 b) {
    return static_cast<uint8_t>(b) & 0b11;
}

enum class MessageType: uint32_t {
    E_STOP = (uint32_t)0,

    // arm
    ENABLE_ARM = (uint32_t)10,
    MOVE_BASE = (uint32_t)11,
    MOVE_SHOULDER = (uint32_t)12,
    MOVE_ELBOW = (uint32_t)13,
    BEND_WRIST = (uint32_t)14,
    TWIST_WRIST = (uint32_t)15,
    MOVE_CLAW = (uint32_t)16,
    MOVE_SOLENOID = (uint32_t)17,

    HEARTBEAT,
};


template <typename T>
CANFrame encode(const T &msg);

template <typename T>
T decode(const CANFrame &frame);
