#include "Arm.h"

void startUp(Dynamixel2Arduino dyna)
{
    pinMode(SHOULDER_DIR_PIN, OUTPUT);
    pinMode(SHOULDER_SPEED_PIN, OUTPUT);
    pinMode(BASE_DIR_PIN, OUTPUT);
    pinMode(BASE_SPEED_PIN, OUTPUT);
    pinMode(ELBOW_DIR_PIN, OUTPUT);
    pinMode(ELBOW_SPEED_PIN, OUTPUT);
    pinMode(GRIPPER_PWM_PIN, OUTPUT);
    pinMode(SOLENOID_PIN, OUTPUT);
    pinMode(STATUS_LIGHT_PIN, OUTPUT);

    Timer1.initialize(TIME);
    Timer1.start();
    Timer3.initialize(TIME);
    Timer3.start();

    SARGripper.attach(GRIPPER_PWM_PIN);

    digitalWrite(STATUS_LIGHT_PIN, HIGH);

    dyna.begin(DYNAMIXEL_BAUD_RATE);
    Serial.printf("set protocol ver: %d\n", dyna.setPortProtocolVersion(DYNAMIXEL_PROTOCOL_VERSION));
    Serial.printf("set torque off 1: %d\n", dyna.torqueOff(1));
    Serial.printf("set torque off 2: %d\n", dyna.torqueOff(2));
    delay(10);
    Serial.printf("operating mode 1: %d\n", dyna.setOperatingMode(1, OP_PWM));
    Serial.printf("operating mode 2: %d\n", dyna.setOperatingMode(2, OP_PWM));
    delay(10);
    Serial.printf("set torque on 1: %d\n", dyna.torqueOn(1));
    Serial.printf("set torque on 2: %d\n", dyna.torqueOn(2));
    delay(10);
    dyna.ping();
    delay(10);
    Serial.printf("ping 1: %d\n", dyna.ping(1));
    Serial.printf("ping 2: %d\n", dyna.ping(2));
    delay(10);
}

void disable(Dynamixel2Arduino dyna)
{
    moveBase(OFF);
    moveShoulder(OFF);
    moveElbow(OFF);
    dyna.torqueOff(DIFFERENCIAL_1);
    dyna.torqueOff(DIFFERENCIAL_2);
    dyna.torqueOff(CLAW);
    is_disabled = true;
}

bool changeDynamixelMotorID(Dynamixel2Arduino dyna, uint8_t oldID, uint8_t newID)
{
    return dyna.setID(oldID, newID);
}

void moveShoulder(Direction direction)
{
    // if disabled then end function
    if (is_disabled)
    {
        return;
    }

    // If direction is not OFF, move motor
    if (direction != OFF)
    {
#if ENABLE_SERIAL
        Serial.println("Moving shoulder");
#endif
        // Write direction, HIGH is one way LOW is the other
        digitalWrite(SHOULDER_DIR_PIN, (int)direction);
        Timer1.pwm(SHOULDER_SPEED_PIN, FIFTY_PERCENT_DUTY_CYCLE);
    }
    // If direction is OFF, stop motor
    else if (direction == OFF)
    {
        Timer1.pwm(SHOULDER_SPEED_PIN, 0);
    }
}

void moveBase(Direction direction)
{
    // if disabled then end function
    if (is_disabled)
    {
        return;
    }

    // If direction is not OFF, move motor
    if (direction != OFF)
    {
#if ENABLE_SERIAL
        Serial.println("Moving base");
#endif
        // Write direction, HIGH is one way LOW is the other
        digitalWrite(BASE_DIR_PIN, (int)direction);
        Timer3.pwm(BASE_SPEED_PIN, FIFTY_PERCENT_DUTY_CYCLE);
    }
    // If direction is OFF, stop motor
    else if (direction == OFF)
    {
        Timer3.pwm(BASE_SPEED_PIN, 0);
    }
}

void newMoveBase(Direction direction)
{
    if (direction != OFF)
    {
        digitalWrite(BASE_DIR_PIN, direction);
        Timer3.pwm(BASE_SPEED_PIN, FIFTY_PERCENT_DUTY_CYCLE);
    }
    else
    {
        Timer3.pwm(BASE_SPEED_PIN, 0);
    }
}

void moveElbow(Direction direction)
{
    // if disabled then end function
    if (is_disabled)
    {
        return;
    }

    // If direction is not OFF, move motor
    if (direction != OFF)
    {
#if ENABLE_SERIAL
        Serial.println("Moving base");
#endif
        // Write direction, HIGH is one way LOW is the other
        digitalWrite(ELBOW_DIR_PIN, (int)direction);
        Timer3.pwm(ELBOW_SPEED_PIN, FIFTY_PERCENT_DUTY_CYCLE);
    }
    // If direction is OFF, stop motor
    else if (direction == OFF)
    {
        Timer3.pwm(ELBOW_SPEED_PIN, 0);
    }
}

// dynamixel 2.0 controls

void bendWrist(Dynamixel2Arduino dyna, Direction direction)
{
    // return if disabled
    if (is_disabled)
    {
        return;
    }

    if (direction == FORWARD)
    {
#if ENABLE_SERIAL
        Serial.println("Bending Wrist Forward");
#endif
        // opposite directions because the differentials face opposite directions on the arm
        dyna.setGoalPWM(DIFFERENCIAL_1, diff1PercentSpeed, UNIT_PERCENT);
        dyna.setGoalPWM(DIFFERENCIAL_2, diff2PercentSpeed * -1, UNIT_PERCENT);
        dyna.torqueOn(DIFFERENCIAL_1);
        dyna.torqueOn(DIFFERENCIAL_2);
    }
    else if (direction == REVERSE)
    {
#if ENABLE_SERIAL
        Serial.println("Bending Wrist Reverse");
#endif
        dyna.setGoalPWM(DIFFERENCIAL_1, diff1PercentSpeed * -1, UNIT_PERCENT);
        dyna.setGoalPWM(DIFFERENCIAL_2, diff2PercentSpeed, UNIT_PERCENT);
        dyna.torqueOn(DIFFERENCIAL_1);
        dyna.torqueOn(DIFFERENCIAL_2);
    }
    else if (direction == OFF)
    {
        dyna.setGoalPWM(DIFFERENCIAL_1, 0, UNIT_PERCENT);
        dyna.setGoalPWM(DIFFERENCIAL_2, 0, UNIT_PERCENT);
        // dyna.torqueOff(DIFFERENCIAL_1);
        // dyna.torqueOff(DIFFERENCIAL_2);
    }
}

void twistWrist(Dynamixel2Arduino dyna, Direction direction)
{
    // return if disabled
    if (is_disabled)
    {
        return;
    }

    if (direction == FORWARD)
    {
#if ENABLE_SERIAL
        Serial.println("Twist Wrist 'Forward'");
#endif
        // same direction because the motors face differentials ways so they rotate the other way naturally
        dyna.setGoalPWM(DIFFERENCIAL_1, diff1PercentSpeed, UNIT_PERCENT);
        dyna.setGoalPWM(DIFFERENCIAL_2, diff2PercentSpeed, UNIT_PERCENT);
        dyna.torqueOn(DIFFERENCIAL_1);
        dyna.torqueOn(DIFFERENCIAL_2);
    }
    else if (direction == REVERSE)
    {
#if ENABLE_SERIAL
        Serial.println("Twist Wrist 'Reverse'");
#endif
        dyna.setGoalPWM(DIFFERENCIAL_1, diff1PercentSpeed * -1, UNIT_PERCENT);
        dyna.setGoalPWM(DIFFERENCIAL_2, diff2PercentSpeed * -1, UNIT_PERCENT);
        dyna.torqueOn(DIFFERENCIAL_1);
        dyna.torqueOn(DIFFERENCIAL_2);
    }
    else if (direction == OFF)
    {
        dyna.setGoalPWM(DIFFERENCIAL_1, 0, UNIT_PERCENT);
        dyna.setGoalPWM(DIFFERENCIAL_2, 0, UNIT_PERCENT);
        // dyna.torqueOff(DIFFERENCIAL_1);
        // dyna.torqueOff(DIFFERENCIAL_2);
    }
}

void moveClaw(Dynamixel2Arduino dyna, Direction direction)
{
    // if disabled then end function
    if (is_disabled)
    {
        return;
    }

    if (direction == FORWARD)
    {
#if ENABLE_SERIAL
        Serial.println("Moving claw Forward");
#endif
        dyna.setGoalPWM(CLAW, clawPercentSpeed, UNIT_PERCENT);
        dyna.torqueOn(CLAW);
    }
    else if (direction == REVERSE)
    {
#if ENABLE_SERIAL
        Serial.println("Moving claw Reverse");
#endif
        dyna.setGoalPWM(CLAW, clawPercentSpeed * -1, UNIT_PERCENT);
        dyna.torqueOn(CLAW);
    }
    else if (direction == OFF)
    {
        dyna.torqueOff(CLAW);
    }
}

void moveSARClaw(Direction direction)
{
    // Serial.println("MOVE SAR CLAW");
    if (is_disabled || direction == Direction::OFF)
    {
        return;
    }

    // Check for Bounds
    if (direction == Direction::FORWARD && gripper_pos >= MAX_GRIPPER_POS)
    {
        return;
    }
    if (direction == Direction::REVERSE && gripper_pos <= MIN_GRIPPER_POS)
    {
        return;
    }

    int mod = 1;
    if (direction == Direction::REVERSE)
    {
        mod = -1;
    }
    gripper_pos += GRIPPER_SPEED * mod;

    Serial.printf("pos: %d\n", gripper_pos);

    SARGripper.write(gripper_pos);
}

void moveSolenoid(int state)
{
    if (is_disabled)
    {
        return;
    }
    digitalWrite(SOLENOID_PIN, state);
}

// others

// void Arm::moveArm(Direction shoulderDirection, Direction wristDirection, Direction elbowDirection, Direction clawDirection)
// {
//   moveShoulder(shoulderDirection);
//   // moveWrist(wristDirection);
//   moveBase(elbowDirection);
//   moveClaw(clawDirection);
// }
