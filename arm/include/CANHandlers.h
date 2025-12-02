#ifndef ARM_CAN_HANDLERS_H
#define ARM_CAN_HANDLERS_H

#include "CAN/messages/arm.h"
#include "CAN/messages/misc.h"

namespace CANHandlers {
void eStop(const EStopMsg &msg);
void enableArm(const EnableArmMsg &msg);
void moveBase(const MoveBaseMsg &msg);
void moveShoulder(const MoveShoulderMsg &msg);
void moveElbow(const MoveElbowMsg &msg);
void bendWrist(const BendWristMsg &msg);
void twistWrist(const TwistWristMsg &msg);
void moveClaw(const MoveClawMsg &msg);
void moveSolenoid(const MoveSolenoidMsg &msg);
}

#endif // ARM_CAN_HANDLERS_H
