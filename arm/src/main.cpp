// Defines root teensy file to run
// Mainly sets callbacks for each CAN message


// Include packages
#include "main.h"
#include "CAN/message_id.h"
#include "CAN/CAN.h"
#include "CANHandlers.h"
#include "Constants.h"

// Define constants
unsigned long previousMillis = 0;
std::shared_ptr<CAN> can;

void setup()
{
    // Serial output
    #if ENABLE_SERIAL
        Serial.begin(9600);
        Serial.println("Arm");
        delay(1000);
    #endif

    // Activate Arm
    Arm::startUp();

    // Define CAN callbacks
    can = std::make_shared<CAN>();
    can->startCAN();
    // XXX: surely a way to infer the type for onMessage given the callback's argument type
    can->onMessage<EStopMsg>(MessageID::E_STOP, CANHandlers::eStop);
    can->onMessage<EnableArmMsg>(MessageID::ENABLE_ARM, CANHandlers::enableArm);
    // can->onMessage<MoveBaseMsg>(MessageID::MOVE_BASE, CANHandlers::moveBase);
    // can->onMessage<MoveShoulderMsg>(MessageID::MOVE_SHOULDER, CANHandlers::moveShoulder);
    // can->onMessage<MoveElbowMsg>(MessageID::MOVE_ELBOW, CANHandlers::moveElbow);
    can->onMessage<BendWristMsg>(MessageID::BEND_WRIST, CANHandlers::bendWrist);
    can->onMessage<TwistWristMsg>(MessageID::TWIST_WRIST, CANHandlers::twistWrist);
    can->onMessage<MoveClawMsg>(MessageID::MOVE_CLAW, CANHandlers::moveClaw);
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


        can->send(HeartbeatMsg{.source = SubSystemID::ARM, .uptime_ms = (u_int32_t)millis(), .enabled = !Arm::isDisabled,}, MessageID::TEENSY_STATUS);
    }

    // Read can data for callbacks (i think)
    can->poll();
}
