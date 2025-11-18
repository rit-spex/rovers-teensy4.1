// Auto-generated encode/decode for ../../include/messages/arm.h
#pragma once

#include "../../include/messages/arm.h"   // struct definitions


// ---------------- Auto-generated encode/decode ----------------





template <>
inline CANFrame encode<EnableArmMsg>(const EnableArmMsg &m) {
    CANFrame frame{};
    frame.id = static_cast<uint32_t>(MessageType::ENABLE_ARM);
    frame.dlc = ENABLE_ARM_DLC;


    frame.data[0] = static_cast<uint8_t>(m.enable);


    return frame;
}

template <>
inline EnableArmMsg decode<EnableArmMsg>(const CANFrame &f) {
    EnableArmMsg m;

    m.enable = static_cast<int>(f.data[0]);

    return m;
}




template <>
inline CANFrame encode<MoveBaseMsg>(const MoveBaseMsg &m) {
    CANFrame frame{};
    frame.id = static_cast<uint32_t>(MessageType::MOVE_BASE);
    frame.dlc = MOVE_BASE_DLC;


    frame.data[0] = static_cast<uint8_t>(m.state);

    frame.data[1] = static_cast<uint8_t>(m.direction);


    return frame;
}

template <>
inline MoveBaseMsg decode<MoveBaseMsg>(const CANFrame &f) {
    MoveBaseMsg m;

    m.state = static_cast<ArmState>(f.data[0]);

    m.direction = static_cast<ArmDir>(f.data[1]);

    return m;
}




template <>
inline CANFrame encode<MoveShoulderMsg>(const MoveShoulderMsg &m) {
    CANFrame frame{};
    frame.id = static_cast<uint32_t>(MessageType::MOVE_SHOULDER);
    frame.dlc = MOVE_SHOULDER_DLC;


    frame.data[0] = static_cast<uint8_t>(m.state);

    frame.data[1] = static_cast<uint8_t>(m.direction);


    return frame;
}

template <>
inline MoveShoulderMsg decode<MoveShoulderMsg>(const CANFrame &f) {
    MoveShoulderMsg m;

    m.state = static_cast<ArmState>(f.data[0]);

    m.direction = static_cast<ArmDir>(f.data[1]);

    return m;
}




template <>
inline CANFrame encode<MoveElbowMsg>(const MoveElbowMsg &m) {
    CANFrame frame{};
    frame.id = static_cast<uint32_t>(MessageType::MOVE_ELBOW);
    frame.dlc = MOVE_ELBOW_DLC;


    frame.data[0] = static_cast<uint8_t>(m.state);

    frame.data[1] = static_cast<uint8_t>(m.direction);


    return frame;
}

template <>
inline MoveElbowMsg decode<MoveElbowMsg>(const CANFrame &f) {
    MoveElbowMsg m;

    m.state = static_cast<ArmState>(f.data[0]);

    m.direction = static_cast<ArmDir>(f.data[1]);

    return m;
}




template <>
inline CANFrame encode<BendWristMsg>(const BendWristMsg &m) {
    CANFrame frame{};
    frame.id = static_cast<uint32_t>(MessageType::BEND_WRIST);
    frame.dlc = BEND_WRIST_DLC;


    frame.data[0] = static_cast<uint8_t>(m.state);

    frame.data[1] = static_cast<uint8_t>(m.direction);


    return frame;
}

template <>
inline BendWristMsg decode<BendWristMsg>(const CANFrame &f) {
    BendWristMsg m;

    m.state = static_cast<ArmState>(f.data[0]);

    m.direction = static_cast<ArmDir>(f.data[1]);

    return m;
}




template <>
inline CANFrame encode<TwistWristMsg>(const TwistWristMsg &m) {
    CANFrame frame{};
    frame.id = static_cast<uint32_t>(MessageType::TWIST_WRIST);
    frame.dlc = TWIST_WRIST_DLC;


    frame.data[0] = static_cast<uint8_t>(m.state);

    frame.data[1] = static_cast<uint8_t>(m.direction);


    return frame;
}

template <>
inline TwistWristMsg decode<TwistWristMsg>(const CANFrame &f) {
    TwistWristMsg m;

    m.state = static_cast<ArmState>(f.data[0]);

    m.direction = static_cast<ArmDir>(f.data[1]);

    return m;
}




template <>
inline CANFrame encode<MoveClawMsg>(const MoveClawMsg &m) {
    CANFrame frame{};
    frame.id = static_cast<uint32_t>(MessageType::MOVE_CLAW);
    frame.dlc = MOVE_CLAW_DLC;


    frame.data[0] = static_cast<uint8_t>(m.state);

    frame.data[1] = static_cast<uint8_t>(m.direction);


    return frame;
}

template <>
inline MoveClawMsg decode<MoveClawMsg>(const CANFrame &f) {
    MoveClawMsg m;

    m.state = static_cast<ArmState>(f.data[0]);

    m.direction = static_cast<ArmDir>(f.data[1]);

    return m;
}




template <>
inline CANFrame encode<MoveSolenoidMsg>(const MoveSolenoidMsg &m) {
    CANFrame frame{};
    frame.id = static_cast<uint32_t>(MessageType::MOVE_SOLENOID);
    frame.dlc = MOVE_SOLENOID_DLC;


    frame.data[0] = static_cast<uint8_t>(m.state);

    frame.data[1] = static_cast<uint8_t>(m.direction);


    return frame;
}

template <>
inline MoveSolenoidMsg decode<MoveSolenoidMsg>(const CANFrame &f) {
    MoveSolenoidMsg m;

    m.state = static_cast<ArmState>(f.data[0]);

    m.direction = static_cast<ArmDir>(f.data[1]);

    return m;
}
