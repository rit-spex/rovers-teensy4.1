#include "CANHandlers.h"

#include <Arduino.h>

#include "Arm.h"
#include "CAN/messages/arm.h"
#include "globals.h"

#define ENABLE_SERIAL 1

static Arm::Direction armStateAndDirToDirection(const ArmState &state, const ArmDir &dir) {
    if (state == ArmState::Stop)  {
        return Arm::Direction::OFF;
    }

    if (dir == ArmDir::Forward) {
        return Arm::Direction::FORWARD;
    }

    if (dir == ArmDir::Reverse) {
        return Arm::Direction::REVERSE;
    }

    return Arm::Direction::OFF;
}

namespace CANHandlers {
void eStop(const EStopMsg &msg) {
#if ENABLE_SERIAL
        Serial.println("ESTOP ENCOUNTERED");
#endif
        Arm::disable();
}
void Heartbeat(const HeartbeatMsg &msg) {
    if(msg.source == SubSystemID::ROS) {
        Arm::lastROSHeartbeatTime = msg.uptime_ms;
#if ENABLE_SERIAL
        Serial.printf("Heartbeat received from ROS with uptime: %l ms", msg.uptime_ms);
#endif
    }
    if (!msg.enabled) 
    {
#if ENABLE_SERIAL
        Serial.println("ROS is disabled. Disabling arm.");
#endif
        Arm::disable();
    }
}
    

void enableArm(const EnableArmMsg &msg) {
    if (msg.enable) {
#if ENABLE_SERIAL
        Serial.println("Enabling Arm");
#endif
        Arm::enable();
    } else {
#if ENABLE_SERIAL
        Serial.println("Disabling Arm");
#endif
        Arm::disable();
    }
}

void moveBase(const MoveBaseMsg &msg) {
    Arm::Direction dir = armStateAndDirToDirection(msg.state, msg.direction);
    Arm::moveBase(dir);
}

void moveShoulder(const MoveShoulderMsg &msg) {
    Arm::Direction dir = armStateAndDirToDirection(msg.state, msg.direction);
    Arm::moveShoulder(dir);
}

void moveElbow(const MoveElbowMsg &msg) {
    Arm::Direction dir = armStateAndDirToDirection(msg.state, msg.direction);
    Arm::moveElbow(dir);
}

void bendWrist(const BendWristMsg &msg) {
    Arm::Direction dir = armStateAndDirToDirection(msg.state, msg.direction);
    Arm::bendWrist(dyna, dir);
}

void twistWrist(const TwistWristMsg &msg) {
    Arm::Direction dir = armStateAndDirToDirection(msg.state, msg.direction);
    Arm::twistWrist(dyna, dir);
}

void moveClaw(const MoveClawMsg &msg) {
    Arm::Direction dir = armStateAndDirToDirection(msg.state, msg.direction);
    Arm::moveSARClaw(dir);
}
void moveSolenoid(const MoveSolenoidMsg &msg) {
    Arm::moveSolenoid(static_cast<int>(msg.state));
}

}
