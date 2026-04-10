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

    // Define CAN callbacks
    can = std::make_shared<CAN>();
    can->startCAN();
    delay(10);


    // TESTING STUFF (Maybe)
    #if TESTING_LIMITS
        Serial.println("--- Beginning Limit Testing Sequence ---");
        Serial.println("Wait 10 secs");
        delay(5000);
        Serial.println("Another 5 to go");
        delay(5000);


        float pos = 45;
        Arm::moveGripper(dyna, pos * 3.14159265/180.0);
        Serial.println("Zero Out Gripper (45deg)");
        delay(5000);
        Serial.println("Another 5 to go");
        delay(5000);


        Serial.println("45->90 Gripper");
        for (pos = 45; pos <= 120; pos = pos+5) {
            Arm::moveGripper(dyna, pos * 3.14159265/180.0);
            delay(1000);
            Serial.print("Enc3: ");
            Serial.print(dyna.getPresentPosition(3));

            Serial.print("    Offset: ");
            Serial.println(dyna.getPresentPosition(3) - dE_3);
            Serial.println(" ");
        }

        delay(2000);
        Arm::updateEncoderAngles();
        delay(1000);
        Arm::updateEncoderAngles();
        delay(2000);

        Serial.println("90->0 Gripper");
        for (pos = 90; pos >= 0; pos = pos-5) {
            Arm::moveGripper(dyna, pos * 3.14159265/180.0);
            delay(1000);
            Serial.print("Enc3: ");
            Serial.print(dyna.getPresentPosition(3));

            Serial.print("    Offset: ");
            Serial.println(dyna.getPresentPosition(3) - dE_3);
            Serial.println(" ");

        }


        delay(2000);
        Arm::updateEncoderAngles();
        delay(1000);
        Arm::updateEncoderAngles();
        delay(2000);

        Serial.println("0->45 Gripper");
        for (pos = 0; pos <= 45; pos = pos+5) {
            Arm::moveGripper(dyna, pos * 3.14159265/180.0);
            delay(1000);
            Serial.print("Enc3: ");
            Serial.print(dyna.getPresentPosition(3));

            Serial.print("    Offset: ");
            Serial.println(dyna.getPresentPosition(3) - dE_3);
            Serial.println(" ");

        }






        Serial.println("Complete Cycle");


        // pos = 20;
        // Arm::moveWrist(dyna, pos * 3.14159265/180, pos * 3.14159265/180.0);
        // Arm::moveGripper(dyna, pos * 3.14159265/180);
        // delay(5000);

        // pos = 180;
        // Arm::moveWrist(dyna, pos * 3.14159265/180, pos * 3.14159265/180.0);
        // Arm::moveGripper(dyna, pos * 3.14159265/180);
        // delay(8000);

        // pos = 10;
        // Arm::moveWrist(dyna, pos * 3.14159265/180, pos * 3.14159265/180.0);
        // Arm::moveGripper(dyna, pos * 3.14159265/180);
        // delay(5000);

        // pos = 30;
        // Arm::moveWrist(dyna, pos * 3.14159265/180, pos * 3.14159265/180.0);
        // Arm::moveGripper(dyna, pos * 3.14159265/180);
        // delay(5000);


        // pos = 100;
        // Arm::moveWrist(dyna, pos * 3.14159265/180, pos * 3.14159265/180.0);
        // Arm::moveGripper(dyna, pos * 3.14159265/180);
        // delay(5000);

        // pos = 100;
        // Arm::moveWrist(dyna, pos * 3.14159265/180, pos * 3.14159265/180.0);
        // Arm::moveGripper(dyna, pos * 3.14159265/180);
        // delay(5000);

        Serial.println("--- Limit Testing Sequence Complete ---");
    #endif

    // Setup callbacks
    // XXX: surely a way to infer the type for onMessage given the callback's argument type
    can->onMessage<EStopMsg>(MessageID::E_STOP, CANHandlers::eStop);
    can->onMessage<EnableArmMsg>(MessageID::ENABLE_ARM, CANHandlers::enableArm);
    can->onMessage<HeartbeatMsg>(MessageID::ROS_HEARTBEAT, CANHandlers::heartbeat);
    // can->onMessage<MoveBaseMsg>(MessageID::MOVE_BASE, CANHandlers::moveBase);
    // can->onMessage<MoveShoulderMsg>(MessageID::MOVE_SHOULDER, CANHandlers::moveShoulder);
    // can->onMessage<MoveElbowMsg>(MessageID::MOVE_ELBOW, CANHandlers::moveElbow);
    can->onMessage<MoveWristMsg>(MessageID::MOVE_WRIST, CANHandlers::moveWrist);
    can->onMessage<MoveGripperMsg>(MessageID::MOVE_GRIPPER, CANHandlers::moveGripper);
    can->onMessage<MoveSolenoidMsg>(MessageID::MOVE_SOLENOID, CANHandlers::moveSolenoid);



}

void loop()
{
    // Prepare LED Control and heartbeat signal
    long currentMillis = millis();
    if (currentMillis - previousMillis >= LED_BLINK_INTERVAL)
    {
        // Update time variable
        previousMillis = currentMillis;
        Serial.println(currentMillis);

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

        if (!Arm::isDisabled)
        {
            // Send-out encoder data
            Arm::updateEncoderAngles();
            ReadWristBendMsg msg1; msg1.position = bendAngle;
            can->send(msg1, MessageID::READ_WRIST_BEND);
            ReadWristTwistMsg msg2; msg2.position = twstAngle;
            can->send(msg2, MessageID::READ_WRIST_TWIST);
            ReadGripperMsg msg3; msg3.position = gripAngle; msg3.state = (gripAngle > 0.1) ? GripperState::Closed : GripperState::Open;
            can->send(msg3, MessageID::READ_GRIPPER);
        }
    }


    if (abs(currentMillis - (long)Arm::lastROSHeartbeatTime) >= TIMEOUT_DURAITON
        && Arm::lastROSHeartbeatTime != 0
        && !Arm::isDisabled) {
                Serial.printf("cur mills %d", currentMillis);
                Serial.printf("last heartbeat %d", Arm::lastROSHeartbeatTime);

        Arm::disable();
        #if ENABLE_SERIAL
                Serial.printf("ROS heartbeat timeout at %lu", currentMillis);
        #endif

    }

    // Read can data for callbacks (i think)
    can->poll();
}
