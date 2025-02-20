#ifndef CAN_H
#define CAN_H

// Constants
#define ActiveCAN CAN::CAN_MODE::CAN2
#define CAN_BAUDRATE 500000
#define MSG_LENGTH 8

// Pinout
enum CAN_PINS
{
	CAN_RX_PIN = 0,
	CAN_TX_PIN = 1
};

#include <ACAN_T4.h>
#include <Arduino.h>
#include <unordered_map>
#include <stdint.h>

class CAN
{
public:
	// temp
	bool m_recievedMsg;
	uint8_t m_lastRecievedMsgCycle;

	typedef enum
	{
		// EStop 0
		// MainBodyBoard 1-9
		// Arm 10-19
		// Science 20-29

		// MainBodyBoard
		E_STOP = (uint32_t)0,
		TARGET_RPM = (uint32_t)1,
		CURRENT_RPM = (uint32_t)2,
		DRIVE_POWER = (uint32_t)3, // this will be left then right power of the wheel, used until encoders are finished

		// Arm
		MOVE_BASE = (uint32_t)10,
		MOVE_SHOULDER = (uint32_t)11,
		MOVE_ELBOW = (uint32_t)12,
		BEND_WRIST = (uint32_t)13,
		TWIST_WRIST = (uint32_t)14,
		MOVE_CLAW = (uint32_t)15
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
	void sendMessage(Message_ID id, uint8_t message[MSG_LENGTH]);

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
