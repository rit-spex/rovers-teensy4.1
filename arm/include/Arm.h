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
    void enable();
    void moveWrist(Dynamixel2Arduino& dyna_ref, float bend, float twist);
    void moveGripper(Dynamixel2Arduino& dyna_ref, float position);
    void homeGripper(Dynamixel2Arduino& dyna_ref);
    void moveSolenoid(int state);
    bool changeDynamixelMotorID(Dynamixel2Arduino& dyna_ref, uint8_t oldID, uint8_t newID);
    void scanDynaBus(Dynamixel2Arduino& dyna_ref);
    void loadStoredMotorData(int32_t& out_saved_M1, int32_t& out_saved_M2);
    void saveContinuousWristData(int32_t absolute_M1, int32_t absolute_M2);

    // Define globals
    extern bool isDisabled;
    extern uint32_t lastROSHeartbeatTime;

}

#endif // ARM_H