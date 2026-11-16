#ifndef CHASSIS_CAN_HANDLERS_H
#define CHASSIS_CAN_HANDLERS_H

#include "CAN/messages/chassis.h"
#include "CAN/messages/misc.h"

#include "constants.h"
#include "chassis.h"
#include "globals.h"

#include <Arduino.h>
#include "ArduinoLog.h"

namespace CANHandlers 
{
    void eStop(const EStopMsg &msg);
    void heartbeat(const HeartbeatMsg &msg);
    void enableChassis(const EnableChassisMsg &msg);
    void drivePower(const DrivePowerMsg &msg);
}

#endif // CHASSIS_CAN_HANDLERS_H
