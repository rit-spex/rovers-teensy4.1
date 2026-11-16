#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cstdint>

// ---------------------------------------------------------------------------
// Compile-time constants for the arm. Runtime state lives in globals.h.
// ---------------------------------------------------------------------------

// ---------------------- Build switches ----------------------
#define ENABLE_SERIAL 1
#define TESTING_LIMITS 0
#define ZERO_OUT_WRIST 0

// ---------------------- Unit conversions ----------------------
constexpr float PI_F = 3.14159265f;
constexpr float DEG_TO_RAD = PI_F / 180.0f;
constexpr float RAD_TO_DEG = 180.0f / PI_F;

// ---------------------- Motor properties ----------------------
// PM42-010-S260-R resolution (ticks per revolution).
constexpr int32_t WRIST_TICKS_PER_REV = 526374 * 0.95f;

// Tick <-> radian coefficients. All joint angles are stored in radians.
constexpr float K_BEND = PI_F / WRIST_TICKS_PER_REV;
constexpr float K_TWST = PI_F / WRIST_TICKS_PER_REV;
constexpr float K_GRIP = 0.00003933284f; // 13 threads per inch, for 1 inch, to go 90 deg

// Ticks between the gripper limit switch and its calibrated zero.
constexpr float GRIPPER_ZERO_OFFSET = -19968.0f;

// ---------------------- Joint limits ----------------------
// Keeping the wrist travel small stops the motor ticks from overflowing the
// Dynamixel extended position range.
constexpr float MAX_BEND_ANGLE = 30.0f * DEG_TO_RAD;
constexpr float MAX_TWIST_ANGLE = 45.0f * DEG_TO_RAD;
constexpr float MIN_GRIPPER_ANGLE = 0.01f; // radians
constexpr float MAX_GRIPPER_ANGLE = 90.0f * DEG_TO_RAD;
constexpr float GRIPPER_TICK_LIMIT = 26000.0f;

// Each wrist motor may not be commanded outside +/- half a revolution.
constexpr int32_t WRIST_TICK_LIMIT = 263187;

// ---------------------- Gripper homing / watchdog ----------------------
constexpr int GRIPPER_HOME_VELOCITY = 1000;
constexpr unsigned long GRIPPER_HOME_TIMEOUT_MS = 15000;   // max time to reach the switch
constexpr unsigned long GRIPPER_SWITCH_POLL_MS = 10;       // limit switch poll interval
constexpr unsigned long GRIPPER_STOP_SETTLE_MS = 100;      // let the motor stop before reading
constexpr unsigned long GRIPPER_COMMAND_TIMEOUT_MS = 500;  // hold if ROS stops commanding

// ---------------------- E-stop ----------------------
constexpr unsigned long ESTOP_CLEAR_DELAY_MS = 1000; // quiet time before an e-stop can be cleared

// ---------------------- Dynamixel ----------------------
#define DYNAMIXEL_PROTOCOL_VERSION 1.0
#define DYNAMIXEL_BAUD_RATE 57600
#define DYNAMIXEL_MOTORS_SERIAL Serial4 // hardware UART for Dynamixels

// ---------------------- Timing ----------------------
constexpr unsigned long LED_BLINK_INTERVAL = 1000 / 10; // milliseconds
constexpr unsigned long TIMEOUT_DURATION = 2000;        // ms without a ROS heartbeat

// ---------------------- Pinout ----------------------
constexpr int LIMIT_SWITCH_PIN = 5;
constexpr int SOLENOID_PIN = 29;
constexpr int STATUS_LIGHT_PIN = 13; // Teensy onboard LED

#endif // CONSTANTS_H
