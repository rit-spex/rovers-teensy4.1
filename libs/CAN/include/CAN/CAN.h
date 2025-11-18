#ifndef CAN_H
#define CAN_H

// Constants
#define ActiveCAN CAN::CAN_MODE::CAN2
#define CAN_BAUDRATE 500000
#define MSG_LENGTH 8

#include <ACAN_T4.h>
#include <Arduino.h>
#include <stdint.h>
#include <unordered_map>

// exports
#include "message_types.h"
#include "can_frame.h"
#include "codec.h"

class CAN
{
public:
    // temp
    bool m_recievedMsg;
    uint8_t m_lastRecievedMsgCycle;

    typedef enum
    {
        CAN1, // this is pins CRX1 and CTX1
        CAN2, // this is pins CRX2 and CTX2
        CAN3  // this is pins CRX3 and CTX3
    } CAN_MODE;

    // this table holds all of the message values
    typedef std::unordered_map<MessageType, CANMessage> ObjectDictionary;

    // this table flags when a new message is found
    typedef std::unordered_map<MessageType, bool> MessageFlag;

    // constructor for the class
    // @param pointer to the programs main cycle
    CAN(unsigned long *currentCycle);

    // start the CAN only call this once
    void startCAN();

    // send message to another device
    void sendMessage(MessageType id, uint8_t message[MSG_LENGTH]);

    // get message out of object dictionary, unpacked. For some unpackage index will matter otherwise not important
    int getUnpackedMessage(MessageType id, int index = 0);

    // get the full data from the object dictionary
    uint8_t *getUnpackedData(MessageType id);

    // emptys out the mailbox in the hardware buffer
    void readMsgBuffer();

    // checks if there has been a new msg on the id
    bool isNewMessage(MessageType id);

    // if the msg is EStop
    static bool IsEStop(const CANMessage &msg);

private:
    unsigned long *m_currentCyclePtr;
    static ObjectDictionary m_objectDict;
    static MessageFlag m_messageFlag;
    static void CANSniff(const CANMessage &msg);
};
#endif
