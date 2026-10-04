// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : main.cpp
// purpose      : This the main file for the chassis.
//                This is the file arduino looks for main
// created on   : 8/14/2025 - Tyler
// last modified: 8/14/2025 - Tyler
// --------------------------------------------------------------------

#include "../include/main.h"

void setup()
{
    // this is the connection to the computer
    Serial.begin(9600);

    // start the logger
    Log.begin(LOG_LEVEL_VERBOSE, &Serial);
    Log.info("Chassis Boot Up\n");

    // start up the main body board, this will turn the status light off
    Chassis::startUp();

    // start Heartbeat timer
    heartbeatTimer = IntervalTimer();
    heartbeatTimer.begin(Chassis::checkHeartbeat, HEARTBEAT_RATE_MS);

    // setup CAN
    can.startCAN();    

    // setup callback
    can.onMessage<EStopMsg>(MessageID::E_STOP, CANHandlers::eStop);
    can.onMessage<HeartbeatMsg>(MessageID::ROS_HEARTBEAT, CANHandlers::heartbeat);
    can.onMessage<DrivePowerMsg>(MessageID::DRIVE_POWER, CANHandlers::drivePower);
    can.onMessage<EnableChassisMsg>(MessageID::ENABLE_CHASSIS, CANHandlers::enableChassis);

}

void loop()
{
    can.poll();
}
