#ifndef CAN_H
#define CAN_H

#include "DEBUG.h"
#include "Pinout.h"
#include "Constants.h"

#if ENABLE_SIMULATOR
#include "../TestSystem/Simulator.h"
#else
// only enable if not using simulator
#include <ACAN_T4.h>
#include <Arduino.h>
#endif

#include <unordered_map>
#include <stdint.h>

class CAN
{
    public:

        // temp
        bool m_recievedMsg;
        uint8_t m_lastRecievedMsgCycle;

        typedef enum {
            E_STOP           = (uint32_t) 0,
            TARGET_RPM       = (uint32_t) 1,
            CURRENT_RPM      = (uint32_t) 2,
            DRIVE_POWER      = (uint32_t) 3  // this will be left then right power of the wheel, used until encoders are finished

        } Message_ID;

        typedef enum
        {
            CAN1, // this is pins CRX1 and CTX1
            CAN2, // this is pins CRX2 and CTX2
            CAN3  // this is pins CRX3 and CTX3
        } CAN_MODE;

        // this table holds all of the message values
        typedef std::unordered_map<Message_ID, CANMessage> ObjectDictionary;

        // this table flags when a new message is found
        typedef std::unordered_map<Message_ID, bool> MessageFlag;

        // constructor for the class
        // @param pointer to the programs main cycle
        CAN(unsigned long *currentCycle);

        // start the CAN only call this once
        void startCAN();

        // send message to another device
        void sendMessage(CAN_MB mailBox, Message_ID id, uint8_t message[MSG_LENGTH]);

        // get message out of object dictionary, unpacked. For some unpackage index will matter otherwise not important
        int getUnpackedMessage(Message_ID id, int index = 0);

        // emptys out the mailbox in the hardware buffer
        void readMsgBuffer();

        // checks if there has been a new msg on the id
        bool isNewMessage(Message_ID id);

        // if the msg is EStop
        static bool IsEStop(const CANMessage &msg);
    private:
        unsigned long *m_currentCyclePtr;
        static ObjectDictionary m_objectDict;
        static MessageFlag m_messageFlag;
        static void CANSniff(const CANMessage &msg);

};
#endif
