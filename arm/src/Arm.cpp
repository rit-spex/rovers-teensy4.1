#include "Arm.h"

#include "Constants.h"

namespace Arm {

    void startUp()
    {
        // Prepare Limit Switch Pin
        // pinMode(LIMIT_SWITCH_PIN, INPUT);

        // Solenoid pin
        pinMode(SOLENOID_PIN, OUTPUT);
        digitalWrite(SOLENOID_PIN, LOW);        // Just to be sure

        // Light pin
        pinMode(STATUS_LIGHT_PIN, OUTPUT);
        digitalWrite(STATUS_LIGHT_PIN, HIGH);

        // Prepare all dynamixel motors
        #if ENABLE_SERIAL
            Serial.println("Activating Dynamixel Communication");
        #endif
        DYNAMIXEL_MOTORS_SERIAL.begin(DYNAMIXEL_BAUD_RATE, SERIAL_8N1);
        delay(50);
        dyna.begin();
        delay(50);

        // Initial Serial Messages
        #if ENABLE_SERIAL

            // // Scan for ALL IDs on bus
            // scanDynaBus(dyna);
            // delay(50);

            // Initialize WRIST_1 (Protocol 2.0)
            dyna.setPortProtocolVersion(2.0);
            delay(50);
            Serial.printf("ping 1: %d\n", dyna.ping(WRIST_1));
            delay(50);
            Serial.printf("set torque off 1: %d\n", dyna.torqueOff(WRIST_1));
            delay(50);
            Serial.printf("operating mode 1: %d\n", dyna.setOperatingMode(WRIST_1, OP_EXTENDED_POSITION));
            delay(50);
            Serial.printf("set torque on 1: %d\n", dyna.torqueOn(WRIST_1));
            delay(50);

            // Initialize WRIST_2 (Protocol 2.0)
            dyna.setPortProtocolVersion(2.0);
            delay(50);
            Serial.printf("ping 2: %d\n", dyna.ping(WRIST_2));
            delay(50);
            Serial.printf("set torque off 2: %d\n", dyna.torqueOff(WRIST_2));
            delay(50);
            Serial.printf("operating mode 2: %d\n", dyna.setOperatingMode(WRIST_2, OP_EXTENDED_POSITION));
            delay(50);
            Serial.printf("set torque on 2: %d\n", dyna.torqueOn(WRIST_2));
            delay(50);

            // Initialize GRIPPER (Protocol 1.0)
            dyna.setPortProtocolVersion(2.0);

            delay(50);
            scanDynaBus(dyna);
            delay(50);

            delay(50);
            Serial.printf("ping 3: %d\n", dyna.ping(GRIPPER));
            delay(50);
            Serial.printf("set torque off 3: %d\n", dyna.torqueOff(GRIPPER));
            delay(50);
            Serial.printf("operating mode 3: %d\n", dyna.setOperatingMode(GRIPPER, OP_EXTENDED_POSITION));
            delay(50);
            Serial.printf("set torque on 3: %d\n", dyna.torqueOn(GRIPPER));
            delay(50);

            uint8_t addrs[] = {0,2,3,4,5,6,8,14,30,32,36,38,40,42,43};
            for (size_t  i = 0; i < sizeof(addrs)/sizeof(addrs[0]); i++) {
                int32_t val = dyna.readControlTableItem(addrs[i], GRIPPER);
                Serial.print("Addr "); Serial.print(addrs[i]);
                Serial.print(" = "); Serial.println(val);
                delay(10);
            }

            Serial.print("Present Position: "); Serial.println(dyna.getPresentPosition(GRIPPER));
            Serial.print("Present Speed   : "); Serial.println(dyna.getPresentVelocity(GRIPPER));
        #endif

        Serial.println("Zero out");
        Arm::bendWrist(dyna, 0 * 3.14159265/180);
        Arm::twistWrist(dyna, 0 * 3.14159265/180);
        delay(5000);

        updateEncoderAngles();

        // Prepare target variables
        targetM1 = enc1;
        targetM2 = enc2;
        targetM3 = enc3;
        bendTarget = bendAngle;
        twstTarget = twstAngle;
        gripTarget = gripAngle;
    }


    void updateEncoderAngles()
    {
        // Define encoder positions
        dyna.setPortProtocolVersion(2.0);
        delay(50);
        enc1 = dyna.getPresentPosition(WRIST_1) - b_1;
        enc2 = dyna.getPresentPosition(WRIST_2) - b_2;
        dyna.setPortProtocolVersion(1.0);
        delay(50);
        enc3 = dyna.getPresentPosition(GRIPPER) - b_3;

        // Interpret angles for differential drive
        bendAngle = k_bend * (enc1 - enc2) / 2.0;
        twstAngle = k_twst * (enc1 + enc2) / 2.0;
        gripAngle = k_grip *  enc3;

        // Print angles
        #if ENABLE_SERIAL
            Serial.println("Updating Encoders");
            Serial.printf(    " M1  : %6.2f  |  M2  : %6.2f  |  M3   : %6.2f\n", enc1, enc2, enc3);
            Serial.printf(    " Bend: %6.2f  | Twist: %6.2f  |  Grip : %6.2f\n", bendAngle*57.295, twstAngle*57.295, gripAngle*57.295);
            // for (int i=1; i< 50; i++) {
            //     Serial.print(i); Serial.print(": ");
            // dyna.setPortProtocolVersion(1.0);
            // delay(50);
            //     Serial.println(dyna.readControlTableItem(i, GRIPPER));
            // }

            Serial.println("");

        #endif

    }


    void disable()
    {
        // moveBase(OFF);
        // moveShoulder(OFF);
        // moveElbow(OFF);
        dyna.setPortProtocolVersion(2.0);
        delay(50);
        dyna.torqueOff(WRIST_1);
        dyna.torqueOff(WRIST_2);
        dyna.setPortProtocolVersion(1.0);
        delay(50);
        dyna.torqueOff(GRIPPER);
        isDisabled = true;
    }


    void enable() {
        isDisabled = false;
    }


    void bendWrist(Dynamixel2Arduino& dyna, float position)
    {
        if (isDisabled) { return; }

        // Bound angles to [-30,30] degrees aka [-0.52359,0.52359] radians
        if (position < -0.52359)
        {
            position = -0.52359;
        }
        else if (position > 0.52359)
        {
            position = 0.52359;
        }

        // Print input
        #if ENABLE_SERIAL
            Serial.print("Bend Angle set to "); Serial.println(position*57.3);
        #endif

        // Compute motor targets
        bendTarget = position;
        targetM1 = ( bendTarget/k_bend + twstTarget/k_twst) + b_1;
        targetM2 = (-bendTarget/k_bend + twstTarget/k_twst) + b_2;

        // Set wrist positions
        dyna.setPortProtocolVersion(2.0);
        delay(50);
        dyna.setGoalPosition(WRIST_1, static_cast<int>(targetM1));
        dyna.setGoalPosition(WRIST_2, static_cast<int>(targetM2));
        delay(50);
    }


    void twistWrist(Dynamixel2Arduino& dyna, float position)
    {
        if (isDisabled) { return; }

        // Bound angles to [-90,90] degrees aka [-1.57079, 1.57079] radians
        if (position < -1.57079)
        {
            position = -1.57079;
        }
        else if (position > 1.57079)
        {
            position = 1.57079;
        }

        // Print input
        #if ENABLE_SERIAL
            Serial.print("Twist Angle set to "); Serial.println(position*57.3);
        #endif

        // Compute motor targets
        twstTarget = position;
        targetM1 = ( bendTarget/k_bend + twstTarget/k_twst) + b_1;
        targetM2 = (-bendTarget/k_bend + twstTarget/k_twst) + b_2;

        // Set wrist positions
        dyna.setPortProtocolVersion(2.0);
        delay(50);
        dyna.setGoalPosition(WRIST_1, static_cast<int>(targetM1));
        dyna.setGoalPosition(WRIST_2, static_cast<int>(targetM2));
        delay(50);
    }


    void moveGripper(Dynamixel2Arduino& dyna, float position)
    {
        if (isDisabled) { return; }

        // Bound angles to [0,90] degrees aka [0, 1.57079] radians
        if (position < 0)
        {
            position = 0;
        }
        else if (position > 1.57079)
        {
            position = 1.57079;
        }

        // Print input
        #if ENABLE_SERIAL
            Serial.print("Gripper Angle set to "); Serial.println(position*57.3);
        #endif

        gripTarget = position;
        targetM3 = gripTarget/k_grip + b_3;
        delay(50);
        dyna.setPortProtocolVersion(1.0);
        delay(50);
        dyna.setGoalPosition(GRIPPER, static_cast<int>(targetM3));
        delay(50);
    }


    void moveSolenoid(int state)
    {
        if (isDisabled)
        {
            return;
        }
        digitalWrite(SOLENOID_PIN, state);
    }


    // These two function are only needed for setting the motor IDs in the development stage, they will remember on power cycle
    bool changeDynamixelMotorID(Dynamixel2Arduino& dyna, uint8_t oldID, uint8_t newID)
    {
        return dyna.setID(oldID, newID);
    }


    void scanDynaBus(Dynamixel2Arduino& dyna)
    {
        Serial.println("Testing DYNAMIXEL Bus");
        for (uint8_t id = 0; id < 255; id++)
        {
            delay(10);
            if (dyna.ping(id))
            {
                Serial.printf("Motor found with ID: %d\n", id);
            }
        }
    }

}








// This code was old ways of driving motors

    // // Move chinese-ium motors

    // void moveShoulder(Direction direction)
    // {
    //     // if disabled then end function
    //     if (isDisabled)
    //     {
    //         return;
    //     }

    //     // If direction is not OFF, move motor
    //     if (direction != OFF)
    //     {
    //         #if ENABLE_SERIAL
    //             Serial.println("Moving shoulder");
    //         #endif
    //         // Write direction, HIGH is one way LOW is the other
    //         digitalWrite(SHOULDER_DIR_PIN, (int)direction);
    //         Timer1.pwm(SHOULDER_SPEED_PIN, FIFTY_PERCENT_DUTY_CYCLE);
    //     }
    //     // If direction is OFF, stop motor
    //     else if (direction == OFF)
    //     {
    //         Timer1.pwm(SHOULDER_SPEED_PIN, 0);
    //     }
    // }

    // void moveBase(Direction direction)
    // {
    //     // if disabled then end function
    //     if (isDisabled)
    //     {
    //         return;
    //     }

    //     // If direction is not OFF, move motor
    //     if (direction != OFF)
    //     {
    //         #if ENABLE_SERIAL
    //             Serial.println("Moving base");
    //         #endif
    //         // Write direction, HIGH is one way LOW is the other
    //         digitalWrite(BASE_DIR_PIN, (int)direction);
    //         Timer3.pwm(BASE_SPEED_PIN, FIFTY_PERCENT_DUTY_CYCLE);
    //     }
    //     // If direction is OFF, stop motor
    //     else if (direction == OFF)
    //     {
    //         Timer3.pwm(BASE_SPEED_PIN, 0);
    //     }
    // }

    // void moveElbow(Direction direction)
    // {
    //     // if disabled then end function
    //     if (isDisabled)
    //     {
    //         return;
    //     }

    //     // If direction is not OFF, move motor
    //     if (direction != OFF)
    //     {
    //         #if ENABLE_SERIAL
    //             Serial.println("Moving base");
    //         #endif
    //         // Write direction, HIGH is one way LOW is the other
    //         digitalWrite(ELBOW_DIR_PIN, (int)direction);
    //         Timer3.pwm(ELBOW_SPEED_PIN, FIFTY_PERCENT_DUTY_CYCLE);
    //     }
    //     // If direction is OFF, stop motor
    //     else if (direction == OFF)
    //     {
    //         Timer3.pwm(ELBOW_SPEED_PIN, 0);
    //     }
    // }

    // dynamixel 2.0 controls

    // void bendWrist(Dynamixel2Arduino dyna, Direction direction)
    // {
    //     // return if disabled
    //     if (isDisabled)
    //     {
    //         return;
    //     }

    //     #if ENABLE_SERIAL
    //         Serial.println("Bending Wrist Forward");
    //     #endif

    //     if (direction == FORWARD)
    //     {
    //         #if ENABLE_SERIAL
    //             Serial.println("Bending Wrist Forward");
    //         #endif
    //         // opposite directions because the differentials face opposite directions on the arm
    //         dyna.setGoalPWM(WRIST_1, diff1PercentSpeed, UNIT_PERCENT);
    //         dyna.setGoalPWM(WRIST_2, diff2PercentSpeed * -1, UNIT_PERCENT);
    //         dyna.torqueOn(WRIST_1);
    //         dyna.torqueOn(WRIST_2);
    //     }
    //     else if (direction == REVERSE)
    //     {
    //         #if ENABLE_SERIAL
    //             Serial.println("Bending Wrist Reverse");
    //         #endif
    //         dyna.setGoalPWM(WRIST_1, diff1PercentSpeed * -1, UNIT_PERCENT);
    //         dyna.setGoalPWM(WRIST_2, diff2PercentSpeed, UNIT_PERCENT);
    //         dyna.torqueOn(WRIST_1);
    //         dyna.torqueOn(WRIST_2);
    //     }
    //     else if (direction == OFF)
    //     {
    //         dyna.setGoalPWM(WRIST_1, 0, UNIT_PERCENT);
    //         dyna.setGoalPWM(WRIST_2, 0, UNIT_PERCENT);
    //         // dyna.torqueOff(WRIST_1);
    //         // dyna.torqueOff(WRIST_2);
    //     }
    // }

    // void twistWrist(Dynamixel2Arduino dyna, Direction direction)
    // {
    //     // return if disabled
    //     if (isDisabled)
    //     {
    //         return;
    //     }

    //     if (direction == FORWARD)
    //     {
    //         #if ENABLE_SERIAL
    //             Serial.println("Twist Wrist 'Forward'");
    //         #endif
    //         // same direction because the motors face differentials ways so they rotate the other way naturally
    //         dyna.setGoalPWM(WRIST_1, diff1PercentSpeed, UNIT_PERCENT);
    //         dyna.setGoalPWM(WRIST_2, diff2PercentSpeed, UNIT_PERCENT);
    //         dyna.torqueOn(WRIST_1);
    //         dyna.torqueOn(WRIST_2);
    //     }
    //     else if (direction == REVERSE)
    //     {
    //         #if ENABLE_SERIAL
    //             Serial.println("Twist Wrist 'Reverse'");
    //         #endif
    //         dyna.setGoalPWM(WRIST_1, diff1PercentSpeed * -1, UNIT_PERCENT);
    //         dyna.setGoalPWM(WRIST_2, diff2PercentSpeed * -1, UNIT_PERCENT);
    //         dyna.torqueOn(WRIST_1);
    //         dyna.torqueOn(WRIST_2);
    //     }
    //     else if (direction == OFF)
    //     {
    //         dyna.setGoalPWM(WRIST_1, 0, UNIT_PERCENT);
    //         dyna.setGoalPWM(WRIST_2, 0, UNIT_PERCENT);
    //         // dyna.torqueOff(WRIST_1);
    //         // dyna.torqueOff(WRIST_2);
    //     }
    // }

    // void moveGripper(Dynamixel2Arduino dyna, Direction direction)
    // {
    //     // if disabled then end function
    //     if (isDisabled)
    //     {
    //         return;
    //     }

    //     if (direction == FORWARD)
    //     {
    //         #if ENABLE_SERIAL
    //             Serial.println("Moving claw Forward");
    //         #endif
    //         dyna.setGoalPWM(GRIPPER, clawPercentSpeed, UNIT_PERCENT);
    //         dyna.torqueOn(GRIPPER);
    //     }
    //     else if (direction == REVERSE)
    //     {
    //         #if ENABLE_SERIAL
    //             Serial.println("Moving claw Reverse");
    //         #endif
    //         dyna.setGoalPWM(GRIPPER, clawPercentSpeed * -1, UNIT_PERCENT);
    //         dyna.torqueOn(GRIPPER);
    //     }
    //     else if (direction == OFF)
    //     {
    //         dyna.torqueOff(GRIPPER);
    //     }
    // }
