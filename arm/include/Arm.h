#ifndef ARM_H
#define ARM_H

#include "Constants.h"
#include <Arduino.h>
#include <Dynamixel2Arduino.h>

namespace Arm {

    enum Dynamixel2MotorIDs
    {
        WRIST_1 = 1,
        WRIST_2 = 2,
        GRIPPER = 3
    };

    // Define functions
    void startUp();
    void updateEncoderAngles();
    void disable();
    void eStop();
    bool enable();
    void updateGripperWatchdog();
    void moveWrist(Dynamixel2Arduino& dyna_ref, float bend, float twist);
    void moveGripper(Dynamixel2Arduino& dyna_ref, float position);
    void homeGripper(Dynamixel2Arduino& dyna_ref);

    // Cycle position -> velocity -> position. Some of these motors will not
    // accept position goals unless the mode has been cycled like this.
    // Sets the mode of one motor; the caller must set the protocol version.
    // Torque is switched off for the cycle; pass true to re-enable it after.
    bool setPositionMode(Dynamixel2Arduino& dyna_ref, uint8_t motorID,
                         bool torqueOnAfter = false);
    void moveSolenoid(int state);
    bool changeDynamixelMotorID(Dynamixel2Arduino& dyna_ref, uint8_t oldID, uint8_t newID);
    void scanDynaBus(Dynamixel2Arduino& dyna_ref);

    // True while the gripper limit switch is pressed (it uses a pull-up).
    bool isLimitSwitchPressed();

    // Debug-only; only called when ZERO_OUT_WRIST is enabled.
    void zeroGripper();

    // Debug-only; only called when TESTING_LIMITS is enabled.
    void testingLimits();

    // Define globals
    extern bool isDisabled;
    extern bool isEStopped;
    extern uint32_t lastROSHeartbeatTime;

    // Gripper command watchdog state
    extern unsigned long lastGripperCmdTime;
    extern bool gripperCmdPending;

    // Time of the last latched e-stop, used to rate-limit clearing it
    extern unsigned long lastEStopTime;

}

#endif // ARM_H