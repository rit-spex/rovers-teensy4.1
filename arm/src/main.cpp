// Defines root teensy file to run
// Mainly sets callbacks for each CAN message

// Include packages
#include "main.h"
#include "Arm.h"
#include "CAN/message_id.h"
#include "CAN/CAN.h"
#include "CAN/messages/arm.h"
#include "CANHandlers.h"
#include "Constants.h"
#include <cstdint>
#include <iterator>

// Should only need one of deez
#include <cstdlib> // Required for integer types
#include <cmath>

// Define constants
unsigned long previousMillis = 0;

#if !TESTING_LIMITS
    std::shared_ptr<CAN> can;
#endif

void setup()
{
    // Serial output
    #if ENABLE_SERIAL
        Serial.begin(9600);
        delay(1000);
        Serial.println("Arm activating");
        delay(1000);
    #endif

    // Activate Arm
    Arm::startUp();

    // Define CAN callbacks
    #if !TESTING_LIMITS
        can = std::make_shared<CAN>();
        can->startCAN();
        delay(10);

        // Setup callbacks
        can->onMessage<EStopMsg>(MessageID::E_STOP, CANHandlers::eStop);
        can->onMessage<EnableArmMsg>(MessageID::ENABLE_ARM, CANHandlers::enableArm);
        can->onMessage<HeartbeatMsg>(MessageID::ROS_HEARTBEAT, CANHandlers::heartbeat);
        // can->onMessage<MoveBaseMsg>(MessageID::MOVE_BASE, CANHandlers::moveBase);
        // can->onMessage<MoveShoulderMsg>(MessageID::MOVE_SHOULDER, CANHandlers::moveShoulder);
        // can->onMessage<MoveElbowMsg>(MessageID::MOVE_ELBOW, CANHandlers::moveElbow);
        can->onMessage<MoveWristMsg>(MessageID::MOVE_WRIST, CANHandlers::moveWrist);
        can->onMessage<MoveGripperMsg>(MessageID::MOVE_GRIPPER, CANHandlers::moveGripper);
        can->onMessage<MoveSolenoidMsg>(MessageID::MOVE_SOLENOID, CANHandlers::moveSolenoid);
    #endif
}

void loop()
{
    // Use unsigned long to safely handle millis() rollover
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= LED_BLINK_INTERVAL)
    {
        Serial.print("Number of bits in my ass: ");
        Serial.println(Serial4.available());
        // Update time variable
        previousMillis = currentMillis;
        // Serial.println(currentMillis); // Optional: uncomment if you want constant terminal spam

        // Arm::isDisabled = (0==1);

        // Updated status light
        if (Arm::isDisabled)
        {
            digitalWrite(STATUS_LIGHT_PIN, HIGH);
        }
        else
        {
            digitalWrite(STATUS_LIGHT_PIN, !digitalRead(STATUS_LIGHT_PIN));
        }

        #if !TESTING_LIMITS
            can->send(
                HeartbeatMsg{
                    .source = SubSystemID::ARM,
                    .uptime_ms = (uint32_t)millis(),
                    .enabled = (uint8_t)(!Arm::isDisabled),
                },
                MessageID::TEENSY_HEARTBEAT
            );

            if (!Arm::isDisabled)
            {
                // Send-out encoder data
                Arm::updateEncoderAngles();
                // Arm::moveWrist(dyna, bendAngle, twstAngle);
                // Arm::moveGripper(dyna, gripAngle);

                // Added Arm:: scope resolution so the compiler knows where to find the variables
                ReadWristBendMsg msg1;
                msg1.position = bendAngle;
                can->send(msg1, MessageID::READ_WRIST_BEND);

                ReadWristTwistMsg msg2;
                msg2.position = twstAngle;
                can->send(msg2, MessageID::READ_WRIST_TWIST);

                ReadGripperMsg msg3;
                msg3.position = gripAngle;
                msg3.state = (gripAngle > 0.1) ? GripperState::Closed : GripperState::Open;
                can->send(msg3, MessageID::READ_GRIPPER);
            }
        #endif
    }

    // Safely check timeout using unsigned math (removed abs() which breaks on rollover)
    if ((currentMillis - Arm::lastROSHeartbeatTime) >= TIMEOUT_DURAITON
        && Arm::lastROSHeartbeatTime != 0
        && !Arm::isDisabled)
    {
        Serial.printf("cur mills %lu\n", currentMillis);
        Serial.printf("last heartbeat %lu\n", Arm::lastROSHeartbeatTime);

        Arm::disable();

        #if ENABLE_SERIAL
            Serial.printf("ROS heartbeat timeout at %lu\n", currentMillis);
        #endif
    }

    #if !TESTING_LIMITS
        // Read can data for callbacks safely within scope
        can->poll();
    #endif
}