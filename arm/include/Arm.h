#ifndef ARM_H
#define ARM_H

// Pull in constants
#include "Constants.h"

// Pull in embedded packages
#include <Arduino.h>
#include <Dynamixel2Arduino.h>


namespace Arm {

    // Enumerates
    // enum Direction
    // {
    //     REVERSE = 0,
    //     FORWARD = 1,
    //     OFF = 2
    // };

    enum Dynamixel2MotorIDs
    {
        WRIST_1 = 1,
        WRIST_2 = 2,
        CLAW = 3
    };

    // Define functions
    void startUp();
    void update_encoder_angles();
    void disable();
    void enable();
    void bendWrist(Dynamixel2Arduino dyna, float position);
    void twistWrist(Dynamixel2Arduino dyna, float position);
    void moveClaw(Dynamixel2Arduino dyna, float position);
    void moveSolenoid(int state);
    bool changeDynamixelMotorID(Dynamixel2Arduino dyna, uint8_t oldID, uint8_t newID);
    void scanDynaBus(Dynamixel2Arduino dyna);

    // Define globals
    extern bool isDisabled;
    extern uint32_t lastROSHeartbeatTime;


}

    // void moveBase(Direction direction);
    // void moveShoulder(Direction direction);
    // void moveElbow(Direction direction);

    // /* FORWARD is down   |   REVERSE is up */
    // void bendWrist(Dynamixel2Arduino dyna, Direction direction);

    // /* FORWARD is counter-clockwise   |    REVERSE is clockwise*/
    // void twistWrist(Dynamixel2Arduino dyna, Direction direction);





#endif
