#ifndef INTLLAB_PUMP
#define INTLLAB_PUMP

#include <Wire.h>

#define SMC_DEVICE_NUM 15

void exitSafeStart();
void setMotorSpeed(int16_t speed);
uint16_t readUpTime();

#endif
