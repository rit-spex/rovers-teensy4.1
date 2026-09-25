#include "CANHandlers.h"

namespace CANHandlers {

    // Handle a E-STOP action
    void eStop(const EStopMsg &msg) 
    {
        Log.error("E-STOP ENCOUNTERED\n");
        Chassis::disable();
    }

    // Respond to the heartbeat
    void heartbeat(const HeartbeatMsg &msg) 
    {
        if (msg.source == SubSystemID::ROS) 
        {
            lastROSHeartbeatTime = millis();
            Log.verbose("Heartbeat received from ROS with uptime: %d ms\n", msg.uptime_ms);
            
            if (!msg.enabled)
            {
                Log.info("ROS is disabled. Disabling Chassis.\n");
                Chassis::disable();
            }
        }
    }

    // Activate chassis
    void enableChassis(const EnableChassisMsg &msg) {
        if (static_cast<bool>(msg.enable)) 
        {
            Chassis::enable();
        } else 
        {
            Chassis::disable();
        }
    }

    void drivePower(const DrivePowerMsg &msg)
    {
        Chassis::drive(msg.left_power, msg.right_power);
    }


}
