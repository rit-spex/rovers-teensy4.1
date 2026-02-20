#include "main.h"
#include "CAN/message_id.h"
#include "CAN/CAN.h"
#include "CANHandlers.h"
#include "globals.h"


unsigned long previousMillis = 0;
unsigned long currentRunCycle = 0;
std::shared_ptr<CAN> can;

void setup()
{
#if ENABLE_SERIAL
    Serial.begin(9600);
    Serial.println("Arm");
    delay(1000);
#endif
    Arm::startUp();

    can = std::make_shared<CAN>();
    can->startCAN();
    // setup message callbacks
    // XXX: surely a way to infer the type for onMessage given the callback's argument type
    can->onMessage<EStopMsg>(MessageID::E_STOP, CANHandlers::eStop);
    can->onMessage<EnableArmMsg>(MessageID::ENABLE_ARM, CANHandlers::enableArm);
    can->onMessage<MoveBaseMsg>(MessageID::MOVE_BASE, CANHandlers::moveBase);
    can->onMessage<MoveShoulderMsg>(MessageID::MOVE_SHOULDER, CANHandlers::moveShoulder);
    can->onMessage<MoveElbowMsg>(MessageID::MOVE_ELBOW, CANHandlers::moveElbow);
    can->onMessage<BendWristMsg>(MessageID::BEND_WRIST, CANHandlers::bendWrist);
    can->onMessage<TwistWristMsg>(MessageID::TWIST_WRIST, CANHandlers::twistWrist);
    can->onMessage<MoveClawMsg>(MessageID::MOVE_CLAW, CANHandlers::moveClaw);
    can->onMessage<MoveSolenoidMsg>(MessageID::MOVE_SOLENOID, CANHandlers::moveSolenoid);
}

void loop()
{
    // Updated status light
    unsigned long currentMillis = millis();
    if (Arm::isDisabled)
    {
        digitalWrite(STATUS_LIGHT_PIN, HIGH);
#if ENABLE_SERIAL
        Serial.println("Status light: Solid");
#endif
    }
    else
    {
        if (currentMillis - previousMillis >= LED_BLINK_INTERVAL)
        {
            previousMillis = currentMillis;
            digitalWrite(STATUS_LIGHT_PIN, !digitalRead(STATUS_LIGHT_PIN));
            can->send(ArmStatusMsg{.estopped = Arm::isDisabled, .enabled = !Arm::isDisabled}, MessageID::ARM_STATUS);
        }
    }

    can->armPoll();
}
