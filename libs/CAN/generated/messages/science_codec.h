// Auto-generated encode/decode for ../../include/messages/science.h
#pragma once

#include "../../include/messages/science.h"   // struct definitions


// ---------------- Auto-generated encode/decode ----------------





template <>
inline CANFrame encode<EnableScienceMsg>(const EnableScienceMsg &m) {
    CANFrame frame{};
    frame.id = static_cast<uint32_t>(MessageType::ENABLE_SCIENCE);
    frame.dlc = ENABLE_SCIENCE_DLC;


    frame.data[0] = static_cast<uint8_t>(m.enable);


    return frame;
}

template <>
inline EnableScienceMsg decode<EnableScienceMsg>(const CANFrame &f) {
    EnableScienceMsg m;

    m.enable = static_cast<uint8_t>(f.data[0]);

    return m;
}




template <>
inline CANFrame encode<MoveAugerMsg>(const MoveAugerMsg &m) {
    CANFrame frame{};
    frame.id = static_cast<uint32_t>(MessageType::MOVE_AUGER);
    frame.dlc = MOVE_AUGER_DLC;


    frame.data[0] = static_cast<uint8_t>(m.state);

    frame.data[1] = static_cast<uint8_t>(m.direction);


    return frame;
}

template <>
inline MoveAugerMsg decode<MoveAugerMsg>(const CANFrame &f) {
    MoveAugerMsg m;

    m.state = static_cast<ScienceState>(f.data[0]);

    m.direction = static_cast<ScienceDir>(f.data[1]);

    return m;
}




template <>
inline CANFrame encode<HomeAugerMsg>(const HomeAugerMsg &m) {
    CANFrame frame{};
    frame.id = static_cast<uint32_t>(MessageType::HOME_AUGER);
    frame.dlc = HOME_AUGER_DLC;



    return frame;
}

template <>
inline HomeAugerMsg decode<HomeAugerMsg>(const CANFrame &f) {
    HomeAugerMsg m;

    return m;
}




template <>
inline CANFrame encode<EnableDrillMsg>(const EnableDrillMsg &m) {
    CANFrame frame{};
    frame.id = static_cast<uint32_t>(MessageType::ENABLE_DRILL);
    frame.dlc = ENABLE_DRILL_DLC;


    frame.data[0] = static_cast<uint8_t>(m.enable);


    return frame;
}

template <>
inline EnableDrillMsg decode<EnableDrillMsg>(const CANFrame &f) {
    EnableDrillMsg m;

    m.enable = static_cast<uint8_t>(f.data[0]);

    return m;
}




template <>
inline CANFrame encode<MoveSlideMsg>(const MoveSlideMsg &m) {
    CANFrame frame{};
    frame.id = static_cast<uint32_t>(MessageType::MOVE_SLIDE);
    frame.dlc = MOVE_SLIDE_DLC;


    frame.data[0] = static_cast<uint8_t>(m.position);


    return frame;
}

template <>
inline MoveSlideMsg decode<MoveSlideMsg>(const CANFrame &f) {
    MoveSlideMsg m;

    m.position = static_cast<SlidePosition>(f.data[0]);

    return m;
}
