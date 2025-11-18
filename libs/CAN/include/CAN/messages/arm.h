#pragma once

#include "arm_codec.h"
#include "CAN/codec.h"

#include <cstdint>

static constexpr uint8_t ENABLE_ARM_DLC = 1;
static constexpr uint8_t MOVE_BASE_DLC = 2;
static constexpr uint8_t MOVE_SHOULDER_DLC = 2;
static constexpr uint8_t MOVE_ELBOW_DLC = 2;
static constexpr uint8_t BEND_WRIST_DLC = 2;
static constexpr uint8_t TWIST_WRIST_DLC = 2;
static constexpr uint8_t MOVE_CLAW_DLC = 2;
static constexpr uint8_t MOVE_SOLENOID_DLC = 2;

struct EnableArmMsg {
    uint8_t enable;
};

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
struct MoveShoulderMsg {
    ArmState state;
    ArmDir direction;
};

struct MoveElbowMsg {
    ArmState state;
    ArmDir direction;
};

struct BendWristMsg {
    ArmState state;
    ArmDir direction;
};

struct TwistWristMsg {
    ArmState state;
    ArmDir direction;
};

struct MoveClawMsg {
    ArmState state;
    ArmDir direction;
};

struct MoveSolenoidMsg {
    ArmState state;
    ArmDir direction;
};
