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

// Define constants
unsigned long previousMillis = 0;
std::shared_ptr<CAN> can;

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
    bool solenoidEnabled = false;       // FIXME: Move to constants???

    // Define CAN callbacks
    can = std::make_shared<CAN>();
    can->startCAN();
    delay(10);

    // Send-out initial encoder data
    ReadWristBendMsg msg1; msg1.position = bendAngle;
    can->send(msg1, MessageID::READ_WRIST_BEND);
    ReadWristTwistMsg msg2; msg2.position = twstAngle;
    can->send(msg2, MessageID::READ_WRIST_TWIST);
    ReadGripperMsg msg3; msg3.position = gripAngle;
    can->send(msg3, MessageID::READ_GRIPPER);

    // TESTING STUFF (Maybe)
    #if TESTING_LIMITS
        Serial.println("Zero out");
        Arm::bendWrist(dyna, 0 * 3.14159265/180);
        Arm::twistWrist(dyna, 0 * 3.14159265/180);
        delay(5000);

        Serial.println("--- Beginning Limit Testing Sequence ---");
        delay(3000);

        float pos = 20;
        // // Arm::bendWrist(dyna, pos * 3.14159265/180);
        Arm::twistWrist(dyna, pos * 3.14159265/180);
        // // Arm::moveGripper(dyna, pos * 3.14159265/180);
        delay(5000);

        pos = 180;
        // // Arm::bendWrist(dyna, pos * 3.14159265/180);
        Arm::twistWrist(dyna, pos * 3.14159265/180);
        // // Arm::moveGripper(dyna, pos * 3.14159265/180);
        delay(8000);

        pos = 10;
        Arm::bendWrist(dyna, pos * 3.14159265/180);
        // Arm::twistWrist(dyna, pos * 3.14159265/180);
        // // Arm::moveGripper(dyna, pos * 3.14159265/180);
        delay(5000);

        pos = 30;
        Arm::bendWrist(dyna, pos * 3.14159265/180);
        // Arm::twistWrist(dyna, pos * 3.14159265/180);
        // // Arm::moveGripper(dyna, pos * 3.14159265/180);
        delay(5000);


        pos = 100;
        Arm::bendWrist(dyna, pos * 3.14159265/180);
        // Arm::twistWrist(dyna, pos * 3.14159265/180);
        // // Arm::moveGripper(dyna, pos * 3.14159265/180);
        delay(5000);

        Serial.println("--- Limit Testing Sequence Complete ---");
    #endif

    // Setup callbacks
    // XXX: surely a way to infer the type for onMessage given the callback's argument type
    can->onMessage<EStopMsg>(MessageID::E_STOP, CANHandlers::eStop);
    can->onMessage<EnableArmMsg>(MessageID::ENABLE_ARM, CANHandlers::enableArm);
    // can->onMessage<MoveBaseMsg>(MessageID::MOVE_BASE, CANHandlers::moveBase);
    // can->onMessage<MoveShoulderMsg>(MessageID::MOVE_SHOULDER, CANHandlers::moveShoulder);
    // can->onMessage<MoveElbowMsg>(MessageID::MOVE_ELBOW, CANHandlers::moveElbow);
    can->onMessage<BendWristMsg>(MessageID::BEND_WRIST, CANHandlers::bendWrist);
    can->onMessage<TwistWristMsg>(MessageID::TWIST_WRIST, CANHandlers::twistWrist);
    can->onMessage<MoveGripperMsg>(MessageID::MOVE_GRIPPER, CANHandlers::moveGripper);
    can->onMessage<MoveSolenoidMsg>(MessageID::MOVE_SOLENOID, CANHandlers::moveSolenoid);



}

void loop()
{
    // Prepare LED Control and heartbeat signal
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= LED_BLINK_INTERVAL)
    {
        // Update time variable
        previousMillis = currentMillis;
        // Updated status light
        if (Arm::isDisabled)
        {
            digitalWrite(STATUS_LIGHT_PIN, HIGH);
        }
        else
        {
            digitalWrite(STATUS_LIGHT_PIN, !digitalRead(STATUS_LIGHT_PIN));
        }


        can->send(
            HeartbeatMsg{
                .source = SubSystemID::ARM,
                .uptime_ms = (uint32_t)millis(),
                .enabled = (uint8_t)(!Arm::isDisabled),
            },
            MessageID::TEENSY_HEARTBEAT
        );

    }

    // Read can data for callbacks (i think)
    can->poll();
}
