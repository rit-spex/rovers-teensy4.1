#include "CAN/CAN.h"
#include <cstdint>
#define ENABLE_SERIAL 1

// Create an object dictionary to store the messages
CAN::ObjectDictionary CAN::m_objectDict;

// Create a message flag map to track new messages
CAN::MessageFlag CAN::m_messageFlag;

CAN::CAN(unsigned long *currentCycle)
{
    m_recievedMsg = false;
    m_currentCyclePtr = currentCycle;
    // Set stop message to 0
    CANMessage stopMessage;
    stopMessage.id = static_cast<uint32_t>(MessageType::E_STOP);
    stopMessage.len = MSG_LENGTH;
    for (int i = 0; i < MSG_LENGTH; i++)
    {
        stopMessage.data[i] = 0;
    }

    m_objectDict[MessageType::E_STOP] = stopMessage;

    // set default speed to 100
    // CANMessage speedMessage;
    // speedMessage.id = MessageType::DRIVE_POWER;
    // speedMessage.len = MSG_LENGTH;
    // speedMessage.data[0] = 100;
    // speedMessage.data[1] = 100;
    //
    // m_objectDict[CAN::Message_ID::DRIVE_POWER] = speedMessage;
}

void CAN::startCAN()
{
    // const ACANPrimaryFilter primaryFilter(&CAN::CANSniff);
    // Set the settings to the CAN
    ACAN_T4_Settings settings(CAN_BAUDRATE);
    settings.mTxPinIsOpenCollector = true;
    settings.mRxPinConfiguration = ACAN_T4_Settings::NO_PULLUP_NO_PULLDOWN;

    // Start the CAN bus based on ActiveCAN
    if (CAN::CAN_MODE::CAN1 == ActiveCAN)
    {
        ACAN_T4::can1.begin(settings); //, &primaryFilter, 1) ;
    }
    else if (CAN::CAN_MODE::CAN2 == ActiveCAN)
    {
        ACAN_T4::can2.begin(settings); //, &primaryFilter, 1) ;
    }
    else if (CAN::CAN_MODE::CAN3 == ActiveCAN)
    {
        ACAN_T4::can3.begin(settings); //, &primaryFilter, 1) ;
    }
#if ENABLE_SERIAL
    Serial.println("CAN StartUp");
#endif
}

// Function to be called when a message is recieved
void CAN::CANSniff(const CANMessage &msg)
{
    MessageType id = static_cast<MessageType>(msg.id);

    // Check if the message will need to be filtered due to an E-Stop
    if (IsEStop(msg))
    {
        m_objectDict.at(MessageType::E_STOP).data[0] = 1;
        return;
    }
    else
    {
        m_objectDict.at(MessageType::E_STOP).data[0] = 0;
    }

    // Check if the ID exists in the m_objectDict map
    if (m_objectDict.find(id) == m_objectDict.end())
    {
        // This is the first time the message with this ID is being received
        m_messageFlag[id] = true;
    }
    // Check if the message has changed and update message flags
    else
    {
        bool newMessage = false;
        const auto &existingMessage = m_objectDict[id];

        for (unsigned int i = 0; i < sizeof(msg.data); i++)
        {
            if (msg.data[i] != existingMessage.data[i])
            {
                newMessage = true;
                break;
            }
        }
        m_messageFlag[id] = newMessage;
    }

    m_objectDict[id] = msg;

#if ENABLE_SERIAL
    Serial.print("Message Received");
    Serial.println(msg.id);
#endif
}

void CAN::readMsgBuffer()
{

    // the current msg
    CANMessage message;

    // get the message from the hardware.
    if (CAN::CAN_MODE::CAN1 == ActiveCAN)
    {
        // if doesn't have message then end
        if (!ACAN_T4::can1.receive(message))
        {
            return;
        }
    }
    else if (CAN::CAN_MODE::CAN2 == ActiveCAN)
    {
        // if doesn't have message then end
        if (!ACAN_T4::can2.receive(message))
        {
            return;
        }
    }
    else if (CAN::CAN_MODE::CAN3 == ActiveCAN)
    {
        // if doesn't have message then end
        if (!ACAN_T4::can3.receive(message))
        {
            return;
        }
    }

    m_lastRecievedMsgCycle = *m_currentCyclePtr;
    m_recievedMsg = true;
    CANSniff(message);
}

// Send a message to the CAN bus
void CAN::sendMessage(MessageType type, uint8_t message[MSG_LENGTH])
{
    // Create a message
    CANMessage msg;

    // Set the message ID to 0x123
    msg.id = static_cast<uint32_t>(type);

    // Set the message length to 8
    msg.len = MSG_LENGTH;

    // Set the message buffer to the m_message buffer
    for (int i = 0; i < MSG_LENGTH; i++)
    {
        msg.data[i] = message[i];
    }

    // Add the message to the object dictionary
    m_objectDict[static_cast<MessageType>(msg.id)] = msg;

    // Send the message
    if (CAN::CAN_MODE::CAN1 == ActiveCAN)
    {
        ACAN_T4::can1.tryToSend(msg);
    }
    else if (CAN::CAN_MODE::CAN2 == ActiveCAN)
    {
        ACAN_T4::can2.tryToSend(msg);
    }
    else if (CAN::CAN_MODE::CAN3 == ActiveCAN)
    {
        ACAN_T4::can3.tryToSend(msg);
    }
}

// get message out of object dictionary, unpacked. For some packages, index will matter otherwise not important
int CAN::getUnpackedMessage(MessageType type, int index)
{
    switch (type)
    {
    case MessageType::E_STOP:
        return m_objectDict.at(MessageType::E_STOP).data[0];
        break;

    default:
        return 0;
        break;
    }
}

uint8_t *CAN::getUnpackedData(MessageType type)
{
    uint8_t *data = m_objectDict.at(type).data;
    return data;
}

// checks if there has been a new msg on the id
bool CAN::isNewMessage(MessageType type)
{
    auto it = m_messageFlag.find(type);
    if (it != m_messageFlag.end())
    {
        return it->second;
    }
    else
    {
        // No message has been received yet at this ID
        return false;
    }
}

bool CAN::IsEStop(const CANMessage &msg)
{
    // if the message E_STOP is off in object dictionary
    if (m_objectDict.at(MessageType::E_STOP).id == 0)
    {
        // if the message is an E-Stop message and the E-Stop is non active turn on the E-Stop
        if (static_cast<MessageType>(msg.id) == MessageType::E_STOP && msg.data[0] == 1)
        {
            // for each message in the object dictionary, set the message flag to true and clear the message buffer
            for (const auto &message : m_objectDict)
            {
                if (message.first != MessageType::E_STOP)
                {
                    m_messageFlag[message.first] = true;
                    for (int i = 0; i < MSG_LENGTH; i++)
                    {
                        m_objectDict[message.first].data[i] = 0;
                    }
                }
            }
            // filter out the message from canSniff
            return true;
        }

        // normal state, do not filter the message
        return false;
    }
    else
    {
        // if the message is an E-Stop message that is and the E-Stop is active turn off the E-Stop
        if (static_cast<MessageType>(msg.id) == MessageType::E_STOP && msg.data[0] == 0)
        {
            // do not filter the message. E-Stop will turn off naturally with canSniff
            return false;
        }
        // E_STOP is active, filter all messages
        return true;
    }
}
