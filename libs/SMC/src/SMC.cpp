#include "SMC.h"

void exitSafeStart()
{
    Wire.beginTransmission(SMC_DEVICE_NUM);
    Wire.write(0x83); // Exit safe start
    Wire.endTransmission();
}

void setMotorSpeed(int16_t speed)
{
    uint8_t cmd = 0x85; // Motor forward
    if (speed < 0)
    {
        cmd = 0x86; // Motor reverse
        speed = -speed;
    }
    Wire.beginTransmission(SMC_DEVICE_NUM);
    Wire.write(cmd);
    Wire.write(speed & 0x1F);
    Wire.write(speed >> 5 & 0x7F);
    Wire.endTransmission();
}

uint16_t readUpTime()
{
    Wire.beginTransmission(SMC_DEVICE_NUM);
    Wire.write(0xA1); // Command: Get variable
    Wire.write(28);   // Variable ID: Up time (low)
    Wire.endTransmission();
    Wire.requestFrom(SMC_DEVICE_NUM, (uint8_t)2);
    uint16_t upTime = Wire.read();
    upTime |= Wire.read() << 8;
    return upTime;
}
