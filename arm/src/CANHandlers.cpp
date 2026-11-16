#include "CANHandlers.h"

#include <Arduino.h>

#include "Arm.h"
#include "CAN/messages/arm.h"
#include "Constants.h"
#include "globals.h"

namespace CANHandlers {

    // Handle a E-STOP action
    void eStop(const EStopMsg &msg) {
        #if ENABLE_SERIAL
            Serial.printf("E-STOP received from subsystem %u\n", static_cast<unsigned>(msg.source));
        #endif
        Arm::eStop();
    }

    // Respond to the heartbeat
    void heartbeat(const HeartbeatMsg &msg) {
        if (msg.source == SubSystemID::ROS) {
            Arm::lastROSHeartbeatTime = millis();
            #if ENABLE_SERIAL
                Serial.printf("Heartbeat received from ROS with uptime: %d ms\n", msg.uptime_ms);
            #endif
        }
        // Any subsystem reporting itself disabled is a shutdown signal. Only act
        // on the transition so an already disabled arm is not re-disabled on
        // every heartbeat.
        if (!msg.enabled && !Arm::isDisabled)
        {
            #if ENABLE_SERIAL
                Serial.println("Heartbeat reports disabled. Disabling arm.");
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
            if (!Arm::enable()) {
                #if ENABLE_SERIAL
                    Serial.println("Arm stays disabled");
                #endif
            }
        } else {
            #if ENABLE_SERIAL
                Serial.println("Disabling Arm");
            #endif
            Arm::disable();
        }
    }

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
