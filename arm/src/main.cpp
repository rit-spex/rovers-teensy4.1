
#include "main.h"

unsigned long previousMillis = 0;
unsigned long currentRunCycle = 0;
std::shared_ptr<CAN> can;
Dynamixel2Arduino dyna(DYNAMIXEL_MOTORS_SERIAL, FULL_DUPLEX_DIR_PIN);

void setup()
{
#if ENABLE_SERIAL
    Serial.begin(9600);
    Serial.println("Arm");
    delay(1000);
#endif
    startUp(dyna);

    can = std::make_shared<CAN>(&currentRunCycle);
    // *can = CAN(&currentRunCycle);
    can->startCAN();
}

void loop()
{
    // Need to call this to read and "sniff" each message
    can->readMsgBuffer();
    if (can->isNewMessage(CAN::ARM_E_STOP))
    {
        disable(dyna);
    }

    // Updated status light
    unsigned long currentMillis = millis();
    if (isDisabled)
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
#if ENABLE_SERIAL
            Serial.printf("Status light: Blink %s\n",
                          digitalRead(STATUS_LIGHT_PIN) ? "HIGH" : "LOW");
#endif
        }
    }

    for (int i = 10; i < 18; ++i)
    {
        if (can->isNewMessage((CAN::Message_ID) i))
        {
            uint8_t *data;
            data = can->getUnpackedData((CAN::Message_ID) i);
#if ENABLE_SERIAL
            Serial.printf("ID %d: [%d, %d]\n", i, data[0], data[1]);
#endif
            Direction direction = (Direction) data[1];
            if (!(bool) data[0])
            {
                direction = OFF;
            }

            // Activate specific motors based on arbitration ID
            switch (i)
            {
            case 11:
                moveBase(direction);
                break;
            case 12:
                moveShoulder(direction);
                break;
            case 13:
                moveElbow(direction);
                break;
            case 14:
                bendWrist(dyna, direction);
                break;
            case 15:
                twistWrist(dyna, direction);
                break;
            case 16:
                moveSARClaw(direction);
                break;
            case 17:
                moveSolenoid(data[0]);
                break;
            default:
#if ENABLE_SERIAL
                Serial.printf("message type not accounted for %d\n", i);
#endif
                disable(dyna);
                break;
            }
        }
    }
}
