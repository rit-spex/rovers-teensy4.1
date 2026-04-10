#include "CANHandlers.h"

#include <Arduino.h>

#include "Arm.h"
#include "CAN/messages/arm.h"
#include "Constants.h"

#define ENABLE_SERIAL 1


namespace CANHandlers {

    // Handle a E-STOP action
    void eStop(const EStopMsg &msg) {
        #if ENABLE_SERIAL
            Serial.println("E-STOP ENCOUNTERED");
        #endif
        Arm::disable();
    }

    // Respond to the heartbeat
    void heartbeat(const HeartbeatMsg &msg) {
        if (msg.source == SubSystemID::ROS) {
            Arm::lastROSHeartbeatTime = millis();
            #if ENABLE_SERIAL
                Serial.printf("Heartbeat received from ROS with uptime: %d ms\n", msg.uptime_ms);
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

    // Activate arm
    void enableArm(const EnableArmMsg &msg) {
        if (static_cast<bool>(msg.enable)) {
            // set the last heartbeat time to now, to prevent the timeout from immediately disabling the arm
            Arm::lastROSHeartbeatTime = millis();
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

    // void moveBase(const MoveBaseMsg &msg) {
    //     Arm::Direction dir = armStateAndDirToDirection(msg.state, msg.direction);
    //     Arm::moveBase(dir);
    // }

    // void moveShoulder(const MoveShoulderMsg &msg) {
    //     Arm::Direction dir = armStateAndDirToDirection(msg.state, msg.direction);
    //     Arm::moveShoulder(dir);
    // }

    // void moveElbow(const MoveElbowMsg &msg) {
    //     Arm::Direction dir = armStateAndDirToDirection(msg.state, msg.direction);
    //     Arm::moveElbow(dir);
    // }

    void moveWrist(const MoveWristMsg &msg) {
        Serial.printf("Wrist received position: bend %f, twist %f\n", msg.position_bend, msg.position_twist);

        Arm::moveWrist(dyna, msg.position_bend, msg.position_twist);
    }
    
    void moveGripper(const MoveGripperMsg &msg) {
        Serial.printf("Move gripper received position: %f\n", msg.position);
        Arm::moveGripper(dyna, msg.position);
    }

    void moveSolenoid(const MoveSolenoidMsg &msg) {
        Arm::moveSolenoid(static_cast<int>(msg.enabled));
    }

}
