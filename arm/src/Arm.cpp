#include "Arm.h"
#include "Constants.h"
#include "globals.h"

namespace Arm {

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
            Serial.printf("set torque off 1: %d\n", dyna.torqueOff(WRIST_1));
            Serial.printf("operating mode 1: %d\n", dyna.setOperatingMode(WRIST_1, OP_EXTENDED_POSITION));
            Serial.printf("set torque on 1: %d\n", dyna.torqueOn(WRIST_1));
        #else
            dyna.ping(WRIST_1);
            dyna.torqueOff(WRIST_1);
            dyna.setOperatingMode(WRIST_1, OP_EXTENDED_POSITION);
            dyna.torqueOn(WRIST_1);
        #endif

        // Initialize WRIST_2 (Protocol 2.0)
        dyna.setPortProtocolVersion(2.0);
        #if ENABLE_SERIAL
            Serial.printf("ping 2: %d\n", dyna.ping(WRIST_2));
            Serial.printf("set torque off 2: %d\n", dyna.torqueOff(WRIST_2));
            Serial.printf("operating mode 2: %d\n", dyna.setOperatingMode(WRIST_2, OP_EXTENDED_POSITION));
            Serial.printf("set torque on 2: %d\n", dyna.torqueOn(WRIST_2));
        #else
            dyna.ping(WRIST_2);
            dyna.torqueOff(WRIST_2);
            dyna.setOperatingMode(WRIST_2, OP_EXTENDED_POSITION);
            dyna.torqueOn(WRIST_2);
        #endif

        // Initialize GRIPPER (Protocol 1.0)
        dyna.setPortProtocolVersion(1.0);
        #if ENABLE_SERIAL
            Serial.printf("ping 3: %d\n", dyna.ping(GRIPPER));
            Serial.printf("set torque off 3: %d\n", dyna.torqueOff(GRIPPER));
            Serial.printf("operating mode 3: %d\n", dyna.setOperatingMode(GRIPPER, OP_EXTENDED_POSITION));
            Serial.printf("set torque on 3: %d\n", dyna.torqueOn(GRIPPER));
        #else
            dyna.ping(GRIPPER);
            dyna.torqueOff(GRIPPER);
            dyna.setOperatingMode(GRIPPER, OP_EXTENDED_POSITION);
            dyna.torqueOn(GRIPPER);
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

        isDisabled = true;
    }


    void enable() {
        // Re-apply torque: disable() turns it off and the motors ignore goal
        // positions until it is turned back on.
        dyna.setPortProtocolVersion(2.0);
        dyna.torqueOn(WRIST_1);
        dyna.torqueOn(WRIST_2);
        dyna.setPortProtocolVersion(1.0);
        dyna.torqueOn(GRIPPER);
        isDisabled = false;
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

        // Strip the multi-turn wrap software offset before sending back to hardware
        dyna_ref.setPortProtocolVersion(2.0);
        dyna_ref.setGoalPosition(WRIST_1, static_cast<int>(targetM1 - wrap_offset_M1));
        dyna_ref.setGoalPosition(WRIST_2, static_cast<int>(targetM2 - wrap_offset_M2));
    }

    void homeGripper(Dynamixel2Arduino& dyna_ref) {
        #if ENABLE_SERIAL
            Serial.println("--- Homing Gripper (to 90 Deg) ---");
        #endif

        // 1. Prepare Limit Switch Pin
        pinMode(LIMIT_SWITCH_PIN, INPUT_PULLUP);

        // 2. Set Gripper to Velocity Mode to drive it continuously
        delay(5);
        dyna_ref.setPortProtocolVersion(1.0);
        dyna_ref.torqueOff(GRIPPER);
        delay(5);
        dyna_ref.setOperatingMode(GRIPPER, OP_VELOCITY);
        delay(5);
        dyna_ref.torqueOn(GRIPPER);

        // 3. Command the gripper to move towards the switch
        delay(5);
        dyna_ref.setGoalVelocity(GRIPPER, 1000);        // 1000 towards limit   2000 away from limit
        delay(5);
        // 4. Wait for the limit switch to trigger
        unsigned long homingStart = millis();
        bool homingSuccess = false;
        delay(500);

        while (millis() - homingStart < 15000) {
            if (digitalRead(LIMIT_SWITCH_PIN) == LOW) {
                homingSuccess = true;
                break;
            }
            delay(10);
        }

        // 5. Stop the motor immediately
        dyna_ref.setGoalVelocity(GRIPPER, 0);
        delay(5);
        dyna_ref.torqueOff(GRIPPER);

        // 6. Handle Homing Result
        if (homingSuccess) {
            #if ENABLE_SERIAL
                Serial.println("Limit Switch Hit! Performing temporary calibration...");
            #endif

            // --- STEP A: TEMPORARY CALIBRATION AT 90 DEG ---
            // We must temporarily calibrate here just so we can safely use moveGripper()
            dyna_ref.setOperatingMode(GRIPPER, OP_EXTENDED_POSITION);
            delay(5);
            dyna_ref.torqueOn(GRIPPER);
            delay(100);

            int32_t raw_90 = dyna_ref.getPresentPosition(GRIPPER);
            delay(5);
            dE_3 = GRIPPER_ZERO_OFFSET;
            wrap_offset_M3 = -GRIPPER_ZERO_OFFSET - raw_90;

            // --- STEP B: MOVE TO 45 DEGREES ---
            #if ENABLE_SERIAL
                Serial.println(raw_90);
                Serial.println(dE_3);
                Serial.println(wrap_offset_M3);
                Serial.println("Moving to 45 deg to escape the hardware wrap boundary...\n");
            #endif

            // Manually move the gripper back
            const float tickLim = GRIPPER_TICK_LIMIT;
            gripTarget = 0;
            targetM3 = max(-tickLim, min(tickLim, gripTarget/K_GRIP + dE_3));
            dyna_ref.setPortProtocolVersion(1.0);
            dyna_ref.setGoalPosition(GRIPPER, static_cast<int>(targetM3));

            // CRITICAL: You must wait long enough for your highly-geared motor to
            // physically reach the 45 degree mark before executing Step C!
            // Adjust this delay if 10 seconds isn't long enough.

            delay(10000);

            // --- STEP C: RE-ANCHOR THE DYNAMIXEL ---
            // Turning torque off and re-applying Extended Position Mode at 45 degrees forces
            // the Dynamixel firmware to reset its "0 rotation" wrap boundary to this new, safe location!
            // Serial.print("Before reanchor: ");
            // Serial.println(dyna_ref.getPresentPosition(GRIPPER));

            dyna_ref.torqueOff(GRIPPER);
            delay(1);
            dyna_ref.setOperatingMode(GRIPPER, OP_EXTENDED_POSITION);
            delay(1);
            dyna_ref.setOperatingMode(GRIPPER, OP_VELOCITY);
            delay(1);
            dyna_ref.setOperatingMode(GRIPPER, OP_EXTENDED_POSITION);
            delay(1);
            dyna_ref.torqueOn(GRIPPER);
            delay(100);

            // --- STEP D: FINAL CALIBRATION AT 45 DEG ---
            #if ENABLE_SERIAL
                Serial.println("Re-anchored! Calculating final offsets...");
            #endif

            int32_t raw_45 = dyna_ref.getPresentPosition(GRIPPER);

            // Calculate where 45 degrees *should* be in ticks based on your existing moveGripper math:
            int32_t ideal_45_ticks = static_cast<int32_t>((45.0 * DEG_TO_RAD) / K_GRIP + GRIPPER_ZERO_OFFSET);

            // Bridge the gap from the new hardware center
            wrap_offset_M3 = ideal_45_ticks - raw_45;

            #if ENABLE_SERIAL
                Serial.println("Homing and Wrap Reset Complete!");
            #endif

        } else {
            #if ENABLE_SERIAL
                Serial.println("ERROR: Gripper Homing Timeout! Limit switch never triggered.");
            #endif
        }
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