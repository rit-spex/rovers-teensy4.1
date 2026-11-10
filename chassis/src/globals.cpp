#include "globals.h"

CAN can = CAN();
bool disabled = true; 
uint32_t lastROSHeartbeatTime = 0; // make heartbeat manager
IntervalTimer heartbeatTimer;

bool m_statusLightOn = false;
IntervalTimer m_statusLEDTimer;
    
// An array of the rover's wheels
Servo m_wheels[NUM_WHEELS];
