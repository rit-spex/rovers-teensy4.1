// ============================================================================
// File: codec.h
//
// Authors:
//     - Lucas Newcomb (@pants721)
//
// Description:
//     Provides the `MessageID` enum which our CAN messages use as identifiers.
// ============================================================================

#ifndef SPEX_CAN_MESSAGE_ID_H
#define SPEX_CAN_MESSAGE_ID_H

#include <cstdint>

enum class MessageID : uint32_t
{
    E_STOP = (uint32_t)0,
    ROS_HEARTBEAT = (uint32_t)1,
    TEENSY_HEARTBEAT = (uint32_t)2,

    // chassis
    ENABLE_CHASSIS = (uint32_t)10,
    DRIVE_POWER = (uint32_t)13,

    // arm
    ENABLE_ARM = (uint32_t)20,
    MOVE_BASE = (uint32_t)21,
    MOVE_SHOULDER = (uint32_t)22,
    MOVE_ELBOW = (uint32_t)23,
    BEND_WRIST = (uint32_t)24,
    TWIST_WRIST = (uint32_t)25,
    MOVE_GRIPPER = (uint32_t)26,
    MOVE_SOLENOID = (uint32_t)27,

    READ_BASE = (uint32_t)30,
    READ_SHOULDER = (uint32_t)31,
    READ_ELBOW = (uint32_t)32,
    READ_WRIST_BEND = (uint32_t)33,
    READ_WRIST_TWIST = (uint32_t)34,
    READ_GRIPPER = (uint32_t)35,

    // science
    ENABLE_SCIENCE = (uint32_t)40,
    MOVE_AUGER = (uint32_t)41,
    ENABLE_DRILL = (uint32_t)42,
    MOVE_SLIDE = (uint32_t)43,
    ENABLE_PUMP = (uint32_t)44,
    MOVE_SPECTROMETER_SLIDE = (uint32_t)48,
    MOVE_FLUOROMETER_SLIDE = (uint32_t)49,
    ENABLE_FLUOROMETER_MICRO_PUMP = (uint32_t)50,
    ENABLE_PRIMER = (uint32_t)51,
    ENABLE_VIBRATION = (uint32_t)52,

    READ_AUGER = (uint32_t)60,
    READ_SLIDE = (uint32_t)61,
    READ_DRILL = (uint32_t)62,
    READ_PUMPS = (uint32_t)63,
    READ_SPECTROMETER_SLIDE = (uint32_t)64,
    READ_FLUOROMETER_SLIDE = (uint32_t)65,
    READ_SPECTROMETER_LIGHT = (uint32_t)66,
    READ_FLUOROMETER_COLOR_SENSOR = (uint32_t)67,
};

#endif // SPEX_CAN_MESSAGE_ID_H
