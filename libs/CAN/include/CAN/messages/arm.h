#pragma once

#include "CAN/codec.h"

#include <cstdint>

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
