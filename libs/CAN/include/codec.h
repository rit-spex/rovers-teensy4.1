#include <cstdint>
#include <array>

struct CANFrame {
    uint32_t id;
    uint8_t dlc;
    std::array<uint8_t, 8> data;
};

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

    // science
    ENABLE_SCIENCE = (uint32_t)20,
    MOVE_AUGER = (uint32_t)21,
    HOME_AUGER = (uint32_t)22,
    ENABLE_DRILL = (uint32_t)23,
    MOVE_SLIDE = (uint32_t)24,

    HEARTBEAT,
};


template <typename T>
CANFrame encode(const T &msg);

template <typename T>
T decode(const CANFrame &frame);
