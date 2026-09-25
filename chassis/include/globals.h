#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include "CAN/CAN.h"
#include <Servo.h>
#include "constants.h"

// ---------------------- Globals ----------------------
extern CAN can;
extern volatile bool disabled; 
extern uint32_t lastROSHeartbeatTime; // make heartbeat manager
extern IntervalTimer heartbeatTimer;

// ---------------------- Chassis ----------------------
extern bool m_statusLightOn;
extern IntervalTimer m_statusLEDTimer;

// An array of the rover's wheels
extern Servo m_wheels[NUM_WHEELS];

#endif // GLOBALS_H