#include "Arm.h"
#include "Constants.h"
#include "globals.h"

namespace Arm {

    // The limit switch uses a pull-up, so a LOW reading means it is pressed.
    bool isLimitSwitchPressed()
    {
        return digitalRead(LIMIT_SWITCH_PIN) == LOW;
    }

    // Position -> velocity -> position. The motors will not accept position
    // goals unless the operating mode is cycled like this first. The mode
    // register can only be written with torque off.
    bool setPositionMode(Dynamixel2Arduino& dyna_ref, uint8_t motorID,
                         bool torqueOnAfter)
    {
        dyna_ref.torqueOff(motorID);
        delay(5);
        dyna_ref.setOperatingMode(motorID, OP_EXTENDED_POSITION);
        delay(5);
        dyna_ref.setOperatingMode(motorID, OP_VELOCITY);
        delay(5);
        bool modeOk = dyna_ref.setOperatingMode(motorID, OP_EXTENDED_POSITION);
        delay(5);

        if (!torqueOnAfter)
        {
            return modeOk;
        }

        bool torqueOk = dyna_ref.torqueOn(motorID);
        return modeOk && torqueOk;
    }

    void startUp()
    {
        // Prepare Limit Switch Pin
        pinMode(LIMIT_SWITCH_PIN, INPUT_PULLUP);

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
        delay(10);
        dyna.begin();
        delay(10);

        // Initialize WRIST_1 (Protocol 2.0)
        dyna.setPortProtocolVersion(2.0);
        #if ENABLE_SERIAL
            Serial.printf("ping 1: %d\n", dyna.ping(WRIST_1));
            Serial.printf("set position mode 1: %d\n", setPositionMode(dyna, WRIST_1, true));
        #else
            dyna.ping(WRIST_1);
            setPositionMode(dyna, WRIST_1, true);
        #endif

        // Initialize WRIST_2 (Protocol 2.0)
        dyna.setPortProtocolVersion(2.0);
        #if ENABLE_SERIAL
            Serial.printf("ping 2: %d\n", dyna.ping(WRIST_2));
            Serial.printf("set position mode 2: %d\n", setPositionMode(dyna, WRIST_2, true));
        #else
            dyna.ping(WRIST_2);
            setPositionMode(dyna, WRIST_2, true);
        #endif

        // Initialize GRIPPER (Protocol 1.0)
        dyna.setPortProtocolVersion(1.0);
        #if ENABLE_SERIAL
            Serial.printf("ping 3: %d\n", dyna.ping(GRIPPER));
            Serial.printf("set position mode 3: %d\n", setPositionMode(dyna, GRIPPER, true));
        #else
            dyna.ping(GRIPPER);
            setPositionMode(dyna, GRIPPER, true);
        #endif

        // ==========================================
        // WRIST MULTI-TURN OFFSETS
        // ==========================================
        // Hardcode the mathematical zero-point so 45 deg evaluates to 0 ticks
        dE_3 = GRIPPER_ZERO_OFFSET;

        // Read the RAW wake-up position of the PM42 motors
        dyna.setPortProtocolVersion(2.0);
        int32_t raw_M1 = dyna.getPresentPosition(WRIST_1);
        int32_t raw_M2 = dyna.getPresentPosition(WRIST_2);

        last_raw_M1 = raw_M1;
        last_raw_M2 = raw_M2;

        // TODO: wrap_offset_M1/M2 are no longer restored from battery-backed RAM.
        // A future implementation will use a gearboxed potentiometer to read the
        // current rotation number and offset the motor ticks accordingly. Until
        // then the offsets stay at zero and the offset math below is a no-op.
        #if ENABLE_SERIAL
            Serial.printf("Loaded M1 Raw: %d | Wrap Offset: %d\n", raw_M1, wrap_offset_M1);
            Serial.printf("Loaded M2 Raw: %d | Wrap Offset: %d\n", raw_M2, wrap_offset_M2);
            Serial.printf("Loaded M3 Gripper Offset: %.2f\n", dE_3);
            Serial.println("Zeroing out wrist");
        #endif

        #if ZERO_OUT_WRIST
            zeroGripper();
        #endif

        Arm::homeGripper(dyna);

        // Update Wrist
        updateEncoderAngles();
        Arm::moveWrist(dyna, 0, 0);
        for (int i = 0; i<10; i++) {
            updateEncoderAngles();
            delay(500);
        }

        // Prepare target variables
        targetM1 = enc1;
        targetM2 = enc2;
        targetM3 = enc3;
        bendTarget = bendAngle;
        twstTarget = twstAngle;
        gripTarget = gripAngle;

        // TESTING STUFF (Maybe)
        #if TESTING_LIMITS
            testingLimits();
        #endif
    }

    void updateEncoderAngles()
    {
        // Define encoder positions
        dyna.setPortProtocolVersion(2.0);
        int32_t raw_M1 = dyna.getPresentPosition(WRIST_1);
        int32_t raw_M2 = dyna.getPresentPosition(WRIST_2);

        // 1. Check for Bus/Communication Errors (Detects Disconnects)
        if (dyna.getLastLibErrCode() != DXL_LIB_OK) {
            Serial.printf("COMM ERROR: Library Code %d\n", dyna.getLastLibErrCode());
            return;
        }

        // 2. The "Motor Off" Check
        // If the reading is exactly 0, we perform a 'Ping' to see if the motor is actually alive.
        // We only do this if it's 0 to avoid slowing down the main loop.
        if (raw_M1 == 0 || raw_M2 == 0) {
            if (!dyna.ping(WRIST_1) || !dyna.ping(WRIST_2)) {
                Serial.println("CRITICAL ERROR: Motor Powered Off or Disconnected!");
                // Optional: Arm::disable();
                return;
            }
        }

        // GUARD: Don't save if the jump is physically impossible in 10ms
        // This should probably be 20k outside of testing limits
        if (abs(raw_M1 - last_raw_M1) > 200000)
        {
            Serial.println("ERROR -> Δ raw_M1 TOO BIG");
            Serial.println(raw_M1);
            Serial.println(last_raw_M1);
            return;
        }
        if (abs(raw_M2 - last_raw_M2) > 200000)
        {
            Serial.println("ERROR -> Δ raw_M2 TOO BIG");
            Serial.println(raw_M2);
            Serial.println(last_raw_M2);
            return;
        }

        last_raw_M1 = raw_M1;
        last_raw_M2 = raw_M2;

        // Add software wrap for multi-turn tracking
        int32_t absolute_M1 = raw_M1 + wrap_offset_M1;
        int32_t absolute_M2 = raw_M2 + wrap_offset_M2;

        enc1 = absolute_M1 - dE_1;
        enc2 = absolute_M2 - dE_2;

        dyna.setPortProtocolVersion(1.0);
        enc3 = dyna.getPresentPosition(GRIPPER) - dE_3;

        // Interpret angles for differential drive
        bendAngle = K_BEND * (enc1 - enc2) / 2.0;
        twstAngle = K_TWST * (enc1 + enc2) / 2.0;
        gripAngle = K_GRIP * enc3;

        // Print angles
        #if ENABLE_SERIAL
            Serial.println("Updating Encoders");
            Serial.printf(    " M1   : %6.2f  |  M2  : %6.2f  |  M3   : %6.2f |\n", enc1, enc2, enc3);
            Serial.printf(    " Bend : %6.2f  | ",   bendAngle*RAD_TO_DEG);
            Serial.printf(    " Twist: %6.2f  | ",   twstAngle*RAD_TO_DEG);
            Serial.printf(    " Grip : %6.2f  |\n", gripAngle*RAD_TO_DEG);
            Serial.println("");
        #endif

    }


    void disable()
    {
        dyna.setPortProtocolVersion(2.0);
        dyna.torqueOff(WRIST_1);
        dyna.torqueOff(WRIST_2);
        dyna.setPortProtocolVersion(1.0);
        dyna.torqueOff(GRIPPER);

        // Fail-safe: de-energize the solenoid whenever the arm is disabled.
        digitalWrite(SOLENOID_PIN, LOW);

        gripperCmdPending = false;
        isDisabled = true;
    }


    // Latch the arm off until a deliberate enable request arrives.
    void eStop()
    {
        isEStopped = true;
        lastEStopTime = millis();

        #if ENABLE_SERIAL
            Serial.println("E-STOP latched");
        #endif

        gripperCmdPending = false;

        if (!isDisabled)
        {
            disable();
        }
        else
        {
            digitalWrite(SOLENOID_PIN, LOW);
        }
    }


    bool enable()
    {
        // Repeated enable requests must not re-latch the goals mid-motion.
        if (!isDisabled && !isEStopped)
        {
            return true;
        }

        if (isEStopped)
        {
            // Require a short quiet period so a held or repeated e-stop cannot be
            // cleared by the next enable request.
            if (millis() - lastEStopTime < ESTOP_CLEAR_DELAY_MS)
            {
                #if ENABLE_SERIAL
                    Serial.println("Enable refused: e-stop is still latched");
                #endif
                return false;
            }

        }

        // Read every joint first so we can hold position instead of snapping to
        // a stale target. If any motor cannot be read, stay disabled.
        dyna.setPortProtocolVersion(2.0);
        int32_t wrist1 = static_cast<int32_t>(dyna.getPresentPosition(WRIST_1));
        bool wrist1Ok = (dyna.getLastLibErrCode() == DXL_LIB_OK);
        int32_t wrist2 = static_cast<int32_t>(dyna.getPresentPosition(WRIST_2));
        bool wrist2Ok = (dyna.getLastLibErrCode() == DXL_LIB_OK);

        dyna.setPortProtocolVersion(1.0);
        int32_t gripper = static_cast<int32_t>(dyna.getPresentPosition(GRIPPER));
        bool gripperOk = (dyna.getLastLibErrCode() == DXL_LIB_OK);

        if (!wrist1Ok || !wrist2Ok || !gripperOk)
        {
            #if ENABLE_SERIAL
                Serial.println("Enable refused: could not read motor positions");
            #endif
            return false;
        }

        // Latch every goal to its current position before applying torque, so a
        // joint does not snap towards a stale target left over from before the
        // disable.
        dyna.setPortProtocolVersion(2.0);
        dyna.setGoalPosition(WRIST_1, wrist1);
        dyna.setGoalPosition(WRIST_2, wrist2);
        dyna.torqueOn(WRIST_1);
        dyna.torqueOn(WRIST_2);

        dyna.setPortProtocolVersion(1.0);
        dyna.setGoalPosition(GRIPPER, gripper);
        dyna.torqueOn(GRIPPER);

        if (isEStopped)
        {
            isEStopped = false;
            #if ENABLE_SERIAL
                Serial.println("E-stop latch cleared");
            #endif
        }

        gripperCmdPending = false;
        isDisabled = false;
        return true;
    }


    // Called every loop: if commands stop arriving, stop chasing the stale goal
    // and hold the gripper where it is.
    void updateGripperWatchdog()
    {
        if (isDisabled || !gripperCmdPending)
        {
            return;
        }

        if (millis() - lastGripperCmdTime < GRIPPER_COMMAND_TIMEOUT_MS)
        {
            return;
        }

        dyna.setPortProtocolVersion(1.0);
        int32_t current = static_cast<int32_t>(dyna.getPresentPosition(GRIPPER));

        if (dyna.getLastLibErrCode() == DXL_LIB_OK)
        {
            dyna.setGoalPosition(GRIPPER, current);
            targetM3 = static_cast<float>(current);
            gripTarget = K_GRIP * (static_cast<float>(current) - dE_3);
        }

        gripperCmdPending = false;

        #if ENABLE_SERIAL
            Serial.println("Gripper command timeout: holding position");
        #endif
    }


    void moveWrist(Dynamixel2Arduino& dyna_ref, float bend, float twist)
    {
        if (isDisabled) { return; }

        // Bound bend to +/-MAX_BEND_ANGLE
        if (bend < -MAX_BEND_ANGLE)
        {
            bend = -MAX_BEND_ANGLE;
        }
        else if (bend > MAX_BEND_ANGLE)
        {
            bend = MAX_BEND_ANGLE;
        }

        // Bound twist to +/-MAX_TWIST_ANGLE
        if (twist < -MAX_TWIST_ANGLE)
        {
            twist = -MAX_TWIST_ANGLE;
        }
        else if (twist > MAX_TWIST_ANGLE)
        {
            twist = MAX_TWIST_ANGLE;
        }

        // Print input
        #if ENABLE_SERIAL
            Serial.print("Bend Angle set to "); Serial.println(bend*RAD_TO_DEG);
            Serial.print("Twist Angle set to "); Serial.println(twist*RAD_TO_DEG);
        #endif

        // Compute motor targets
        bendTarget = bend;
        twstTarget = twist;
        targetM1 = ( bendTarget/K_BEND + twstTarget/K_TWST) + dE_1;
        targetM2 = (-bendTarget/K_BEND + twstTarget/K_TWST) + dE_2;

        // Strip the multi-turn wrap software offset before sending back to
        // hardware, then keep each motor inside its +/- limit.
        int32_t goalM1 = static_cast<int32_t>(targetM1 - wrap_offset_M1);
        int32_t goalM2 = static_cast<int32_t>(targetM2 - wrap_offset_M2);
        goalM1 = max(-WRIST_TICK_LIMIT, min(WRIST_TICK_LIMIT, goalM1));
        goalM2 = max(-WRIST_TICK_LIMIT, min(WRIST_TICK_LIMIT, goalM2));

        dyna_ref.setPortProtocolVersion(2.0);
        dyna_ref.setGoalPosition(WRIST_1, goalM1);
        dyna_ref.setGoalPosition(WRIST_2, goalM2);
    }

    // Drive the gripper into its limit switch, then treat that position as the
    // zero. The gripper ends up at its calibrated rest position.
    void homeGripper(Dynamixel2Arduino& dyna_ref) {
        #if ENABLE_SERIAL
            Serial.println("--- Homing Gripper ---");
        #endif

        pinMode(LIMIT_SWITCH_PIN, INPUT_PULLUP);

        dyna_ref.setPortProtocolVersion(1.0);
        dyna_ref.torqueOff(GRIPPER);
        delay(5);

        // If the button is already pressed, there is nothing to drive.
        bool homed = false;
        if (isLimitSwitchPressed())
        {
            delay(GRIPPER_SWITCH_POLL_MS);
            homed = isLimitSwitchPressed();
        }

        if (!homed)
        {
            // Drive towards the button in velocity mode.
            dyna_ref.setOperatingMode(GRIPPER, OP_VELOCITY);
            delay(5);
            dyna_ref.setGoalVelocity(GRIPPER, GRIPPER_HOME_VELOCITY);
            dyna_ref.torqueOn(GRIPPER);

            // A press only counts once two consecutive readings agree, so a
            // bounce cannot stop the motor early.
            bool wasPressed = false;
            unsigned long start = millis();
            while (millis() - start < GRIPPER_HOME_TIMEOUT_MS)
            {
                bool pressed = isLimitSwitchPressed();

                if (pressed && wasPressed)
                {
                    homed = true;
                    break;
                }

                wasPressed = pressed;
                delay(GRIPPER_SWITCH_POLL_MS);
            }

            // Stop where the button was hit and let the motor settle.
            dyna_ref.setGoalVelocity(GRIPPER, 0);
            delay(GRIPPER_STOP_SETTLE_MS);
            dyna_ref.torqueOff(GRIPPER);
            delay(5);
        }

        // Always leave the motor in position mode, so a later enable does not
        // run it away in velocity mode.
        setPositionMode(dyna_ref, GRIPPER);

        if (!homed)
        {
            #if ENABLE_SERIAL
                Serial.println("ERROR: Gripper never reached the limit switch");
            #endif
            return;
        }

        int32_t switchTicks = static_cast<int32_t>(dyna_ref.getPresentPosition(GRIPPER));
        if (dyna_ref.getLastLibErrCode() != DXL_LIB_OK)
        {
            #if ENABLE_SERIAL
                Serial.println("ERROR: Could not read the gripper at the limit switch");
            #endif
            return;
        }

        // The calibrated zero sits GRIPPER_ZERO_OFFSET ticks from the button.
        dE_3 = static_cast<float>(switchTicks) + GRIPPER_ZERO_OFFSET;

        #if ENABLE_SERIAL
            Serial.printf("Gripper switch at %ld ticks, zero at %.0f\n",
                          static_cast<long>(switchTicks), dE_3);
        #endif

        // Move off the button to the rest position; the main loop takes over.
        gripTarget = 0.0f;
        targetM3 = max(-GRIPPER_TICK_LIMIT,
                       min(GRIPPER_TICK_LIMIT, gripTarget / K_GRIP + dE_3));
        dyna_ref.setGoalPosition(GRIPPER, static_cast<int>(targetM3));
        delay(5);
        dyna_ref.torqueOn(GRIPPER);
    }

    void moveGripper(Dynamixel2Arduino& dyna_ref, float position)
    {
        if (isDisabled) { return; }

        const float tickLim = GRIPPER_TICK_LIMIT;

        // Bound angles to [MIN_GRIPPER_ANGLE, MAX_GRIPPER_ANGLE]
        if (position < MIN_GRIPPER_ANGLE)
        {
            position = MIN_GRIPPER_ANGLE;
        }
        else if (position > MAX_GRIPPER_ANGLE)
        {
            position = MAX_GRIPPER_ANGLE;
        }

        // Print input
        #if ENABLE_SERIAL
            Serial.print("Gripper Angle set to "); Serial.println(position*RAD_TO_DEG);
        #endif

        gripTarget = position;
        targetM3 = max(-tickLim, min(tickLim, gripTarget/K_GRIP + dE_3));

        dyna_ref.setPortProtocolVersion(1.0);
        dyna_ref.setGoalPosition(GRIPPER, static_cast<int>(targetM3));

        // Feed the command watchdog.
        lastGripperCmdTime = millis();
        gripperCmdPending = true;
    }


    void moveSolenoid(int state)
    {
        if (isDisabled) {return;}
        #if ENABLE_SERIAL
        Serial.printf("Solenoid State %d", state);
        #endif

        digitalWrite(SOLENOID_PIN, state);
    }


    // These two function are only needed for setting the motor IDs in the development stage, they will remember on power cycle
    bool changeDynamixelMotorID(Dynamixel2Arduino& dyna_ref, uint8_t oldID, uint8_t newID)
    {
        return dyna_ref.setID(oldID, newID);
    }


    void scanDynaBus(Dynamixel2Arduino& dyna_ref)
    {
        Serial.println("Testing DYNAMIXEL Bus");
        for (uint8_t id = 0; id < 255; id++)
        {
            delay(10);
            if (dyna_ref.ping(id))
            {
                Serial.printf("Motor found with ID: %d\n", id);
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    //                                   Debugging Functions
    /////////////////////////////////////////////////////////////////////////////////////////////

    void zeroGripper()
    {
        // RE-ZERO OUT
        Serial.println("Pre-Zero Read");
        Arm::updateEncoderAngles();
        dyna.setPortProtocolVersion(2.0);
        dyna.setGoalPosition(Arm::Dynamixel2MotorIDs::WRIST_1, 0);
        dyna.setGoalPosition(Arm::Dynamixel2MotorIDs::WRIST_2, 0);
        for (int i = 0; i<10; i++)
        {
            Arm::updateEncoderAngles();
            delay(500);
        }
        Serial.println("Post-Zero Read");
        Arm::updateEncoderAngles();
        Serial.print("Raw Wrist 1: ");
        Serial.println(dyna.getPresentPosition(Arm::Dynamixel2MotorIDs::WRIST_1));
        Serial.print("Raw Wrist 2: ");
        Serial.println(dyna.getPresentPosition(Arm::Dynamixel2MotorIDs::WRIST_2));
        // Wrist position is no longer persisted to battery-backed RAM, so there
        // is nothing to zero here.
        Serial.println("Kill Power");
        delay(10000000);
    }

    void testingLimits()
    {
        Serial.println("--- Beginning Limit Testing Sequence ---");
        Serial.println("In like 5 secondos");
        delay(5000);

        int pos = 45;
        // Serial.println("45->90 Gripper");
        // for (pos = 45; pos <= 120; pos = pos+5) {
        //     Arm::moveGripper(dyna, pos * DEG_TO_RAD);
        //     delay(1000);
        //     Serial.print("Enc3: ");
        //     Serial.print(dyna.getPresentPosition(3));

        //     Serial.print("    Offset: ");
        //     Serial.println(dyna.getPresentPosition(3) - dE_3);
        //     Serial.println(" ");
        // }

        // delay(2000);
        // Arm::updateEncoderAngles();
        // delay(1000);
        // Arm::updateEncoderAngles();
        // delay(2000);

        // Serial.println("90->0 Gripper");
        // for (pos = 90; pos >= 0; pos = pos-5) {
        //     Arm::moveGripper(dyna, pos * DEG_TO_RAD);
        //     delay(1000);
        //     Serial.print("Enc3: ");
        //     Serial.print(dyna.getPresentPosition(3));

        //     Serial.print("    Offset: ");
        //     Serial.println(dyna.getPresentPosition(3) - dE_3);
        //     Serial.println(" ");

        // }


        // delay(2000);
        // Arm::updateEncoderAngles();
        // delay(1000);
        // Arm::updateEncoderAngles();
        // delay(2000);

        // Serial.println("0->45 Gripper");
        // for (pos = 0; pos <= 45; pos = pos+5) {
        //     Arm::moveGripper(dyna, pos * DEG_TO_RAD);
        //     delay(1000);
        //     Serial.print("Enc3: ");
        //     Serial.print(dyna.getPresentPosition(3));

        //     Serial.print("    Offset: ");
        //     Serial.println(dyna.getPresentPosition(3) - dE_3);
        //     Serial.println(" ");

        // }

        // Serial.println("Complete Cycle");
        pos = 10;
        Arm::moveWrist(dyna, pos * DEG_TO_RAD, pos*2 * DEG_TO_RAD);

        // Arm::moveGripper(dyna, pos * DEG_TO_RAD);
        for (int i = 0; i<10; i++) {
            updateEncoderAngles();
            delay(500);
        }

        pos = 20;
        Arm::moveWrist(dyna, pos * DEG_TO_RAD, pos*3 * DEG_TO_RAD);
        // Arm::moveGripper(dyna, pos * DEG_TO_RAD);
        for (int i = 0; i<10; i++) {
            updateEncoderAngles();
            delay(500);
        }

        updateEncoderAngles();

        pos = 30;
        Arm::moveWrist(dyna, pos * DEG_TO_RAD, pos*4 * DEG_TO_RAD);
        // Arm::moveGripper(dyna, pos * DEG_TO_RAD);
        for (int i = 0; i<10; i++) {
            updateEncoderAngles();
            delay(500);
        }

        updateEncoderAngles();

        pos = 50;
        Arm::moveWrist(dyna, pos * DEG_TO_RAD, pos*5 * DEG_TO_RAD);
        // Arm::moveGripper(dyna, pos * DEG_TO_RAD);
        for (int i = 0; i<10; i++) {
            updateEncoderAngles();
            delay(500);
        }

        updateEncoderAngles();



        pos = 0;
        Arm::moveWrist(dyna, pos * DEG_TO_RAD, pos*5 * DEG_TO_RAD);
        // Arm::moveGripper(dyna, pos * DEG_TO_RAD);
        for (int i = 0; i<10; i++) {
            updateEncoderAngles();
            delay(500);
        }

        pos = -90;
        Arm::moveWrist(dyna, pos * DEG_TO_RAD, pos*5 * DEG_TO_RAD);
        // Arm::moveGripper(dyna, pos * DEG_TO_RAD);
        for (int i = 0; i<10; i++) {
            updateEncoderAngles();
            delay(500);
        }

        updateEncoderAngles();


        Serial.println("--- Limit Testing Sequence Complete ---");
    }

}