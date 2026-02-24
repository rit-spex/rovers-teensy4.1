#include "CAN/codec.h"

CANMessage buildArmMsg(int deviceIdx, uint32_t operationCode, uint64_t data,
                       int length, int idCode) {
    CANMessage message;
    message.id = DEVICE_ID_OFFSET_SEND + deviceIdx;
    message.len = length;
    message.data[0] = idCode;
    message.data[1] = operationCode & 0xff;
    message.data[2] = (operationCode >> 8) & 0xff;
    message.data[3] = 0x00;
    if (length > 4) {
        message.data[4] = (data >> 0) & 0xff;
        message.data[5] = (data >> 8) & 0xff;
        message.data[6] = (data >> 16) & 0xff;
        message.data[7] = (data >> 24) & 0xff;
    }

    return message;
}
