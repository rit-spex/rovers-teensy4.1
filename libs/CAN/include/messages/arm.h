#pragma once

#include "../codec.h"
#include <cstdint>

static constexpr uint8_t ENABLE_ARM_DLC = 1;
// I think all arm commands want to have a dlc of 8
static constexpr uint8_t ARM_COMMAND_DLC = 8;

struct EnableArmMsg {
    Bool2 enable;
};

template <>
inline CANFrame encode<EnableArmMsg>(const EnableArmMsg &m) {
    CANFrame frame{};
    frame.id = static_cast<uint32_t>(MessageType::ENABLE_ARM);
    frame.dlc = ENABLE_ARM_DLC;

    frame.data[0] = pack_bool_2(m.enable);

    return frame;
}

template <>
inline EnableArmMsg decode<EnableArmMsg>(const CANFrame &f) {
    EnableArmMsg m;
    uint8_t enable_val = f.data[0] & 0b11;

    switch (enable_val) {
        case 0b01: m.enable = Bool2::Off; break;
        case 0b10: m.enable = Bool2::On; break;
        default: m.enable = Bool2::Invalid; break;
    }

    return m;
}

// ARM COMMANDS

enum class ArmState : uint8_t {
    Active = 0,
    Stop = 1,
};

enum class ArmDir : uint8_t {
    Reverse = 0,
    Forward = 1,
};

struct MoveBaseMsg {
    ArmState state;
    ArmDir direction;
};

template <>
inline CANFrame encode<MoveBaseMsg>(const MoveBaseMsg &m) {
    CANFrame frame{};
    frame.id = static_cast<uint32_t>(MessageType::MOVE_BASE);
    frame.dlc = ARM_COMMAND_DLC;

    frame.data[0] = static_cast<uint8_t>(m.state);
    frame.data[1] = static_cast<uint8_t>(m.direction);

    for (int i = 2; i < ARM_COMMAND_DLC; ++i) {
        frame.data[i] = 0;
    }

    return frame;
}

template <>
inline MoveBaseMsg decode<MoveBaseMsg>(const CANFrame &f) {
    MoveBaseMsg m;
    m.state = static_cast<ArmState>(f.data[0] & 0x01);
    m.direction = static_cast<ArmDir>(f.data[1] & 0x01);

    return m;
}

// Other arm part commands follow the same two-byte (state + direction) layout

struct MoveShoulderMsg {
    ArmState state;
    ArmDir direction;
};

template <>
inline CANFrame encode<MoveShoulderMsg>(const MoveShoulderMsg &m) {
    CANFrame frame{};
    frame.id = static_cast<uint32_t>(MessageType::MOVE_SHOULDER);
    frame.dlc = ARM_COMMAND_DLC;

    frame.data[0] = static_cast<uint8_t>(m.state);
    frame.data[1] = static_cast<uint8_t>(m.direction);

    for (int i = 2; i < ARM_COMMAND_DLC; ++i) {
        frame.data[i] = 0;
    }

    return frame;
}

template <>
inline MoveShoulderMsg decode<MoveShoulderMsg>(const CANFrame &f) {
    MoveShoulderMsg m;
    m.state = static_cast<ArmState>(f.data[0] & 0x01);
    m.direction = static_cast<ArmDir>(f.data[1] & 0x01);
    return m;
}

struct MoveElbowMsg {
    ArmState state;
    ArmDir direction;
};

template <>
inline CANFrame encode<MoveElbowMsg>(const MoveElbowMsg &m) {
    CANFrame frame{};
    frame.id = static_cast<uint32_t>(MessageType::MOVE_ELBOW);
    frame.dlc = ARM_COMMAND_DLC;

    frame.data[0] = static_cast<uint8_t>(m.state);
    frame.data[1] = static_cast<uint8_t>(m.direction);

    for (int i = 2; i < ARM_COMMAND_DLC; ++i) {
        frame.data[i] = 0;
    }

    return frame;
}

template <>
inline MoveElbowMsg decode<MoveElbowMsg>(const CANFrame &f) {
    MoveElbowMsg m;
    m.state = static_cast<ArmState>(f.data[0] & 0x01);
    m.direction = static_cast<ArmDir>(f.data[1] & 0x01);
    return m;
}

struct BendWristMsg {
    ArmState state;
    ArmDir direction;
};

template <>
inline CANFrame encode<BendWristMsg>(const BendWristMsg &m) {
    CANFrame frame{};
    frame.id = static_cast<uint32_t>(MessageType::BEND_WRIST);
    frame.dlc = ARM_COMMAND_DLC;

    frame.data[0] = static_cast<uint8_t>(m.state);
    frame.data[1] = static_cast<uint8_t>(m.direction);

    for (int i = 2; i < ARM_COMMAND_DLC; ++i) {
        frame.data[i] = 0;
    }

    return frame;
}

template <>
inline BendWristMsg decode<BendWristMsg>(const CANFrame &f) {
    BendWristMsg m;
    m.state = static_cast<ArmState>(f.data[0] & 0x01);
    m.direction = static_cast<ArmDir>(f.data[1] & 0x01);
    return m;
}

struct TwistWristMsg {
    ArmState state;
    ArmDir direction;
};

template <>
inline CANFrame encode<TwistWristMsg>(const TwistWristMsg &m) {
    CANFrame frame{};
    frame.id = static_cast<uint32_t>(MessageType::TWIST_WRIST);
    frame.dlc = ARM_COMMAND_DLC;

    frame.data[0] = static_cast<uint8_t>(m.state);
    frame.data[1] = static_cast<uint8_t>(m.direction);

    for (int i = 2; i < ARM_COMMAND_DLC; ++i) {
        frame.data[i] = 0;
    }

    return frame;
}

template <>
inline TwistWristMsg decode<TwistWristMsg>(const CANFrame &f) {
    TwistWristMsg m;
    m.state = static_cast<ArmState>(f.data[0] & 0x01);
    m.direction = static_cast<ArmDir>(f.data[1] & 0x01);
    return m;
}

struct MoveClawMsg {
    ArmState state;
    ArmDir direction;
};

template <>
inline CANFrame encode<MoveClawMsg>(const MoveClawMsg &m) {
    CANFrame frame{};
    frame.id = static_cast<uint32_t>(MessageType::MOVE_CLAW);
    frame.dlc = ARM_COMMAND_DLC;

    frame.data[0] = static_cast<uint8_t>(m.state);
    frame.data[1] = static_cast<uint8_t>(m.direction);

    for (int i = 2; i < ARM_COMMAND_DLC; ++i) {
        frame.data[i] = 0;
    }

    return frame;
}

template <>
inline MoveClawMsg decode<MoveClawMsg>(const CANFrame &f) {
    MoveClawMsg m;
    m.state = static_cast<ArmState>(f.data[0] & 0x01);
    m.direction = static_cast<ArmDir>(f.data[1] & 0x01);
    return m;
}

struct MoveSolenoidMsg {
    ArmState state;
    ArmDir direction;
};

template <>
inline CANFrame encode<MoveSolenoidMsg>(const MoveSolenoidMsg &m) {
    CANFrame frame{};
    frame.id = static_cast<uint32_t>(MessageType::MOVE_SOLENOID);
    frame.dlc = ARM_COMMAND_DLC;

    frame.data[0] = static_cast<uint8_t>(m.state);
    frame.data[1] = static_cast<uint8_t>(m.direction);

    for (int i = 2; i < ARM_COMMAND_DLC; ++i) {
        frame.data[i] = 0;
    }

    return frame;
}

template <>
inline MoveSolenoidMsg decode<MoveSolenoidMsg>(const CANFrame &f) {
    MoveSolenoidMsg m;
    m.state = static_cast<ArmState>(f.data[0] & 0x01);
    m.direction = static_cast<ArmDir>(f.data[1] & 0x01);
    return m;
}
