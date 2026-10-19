#ifndef CONSTANTS_H
#define CONSTANTS_H

// --- Battery-Backed RAM Registers --- (Apparently not needed with PlatformIO, but imma leave it incase any stuff doesnt use that ya know)
// #define SNVS_LPGPR0 (*(volatile uint32_t *)0x400A4000) // Wrist M1 Wrap
// #define SNVS_LPGPR1 (*(volatile uint32_t *)0x400A4004) // Wrist M2 Wrap
// #define SNVS_LPGPR2 (*(volatile uint32_t *)0x400A4008) // Gripper M3 Offset

#define ENABLE_SERIAL 1
#define TESTING_LIMITS 0
#define ZERO_OUT_WRIST 0
#define ENABLE_SERIAL 1

// ---------------------- Dynamixel ----------------------
#define DYNAMIXEL_PROTOCOL_VERSION 1.0
#define DYNAMIXEL_BAUD_RATE 57600
#define DYNAMIXEL_MOTORS_SERIAL Serial4 // hardware UART for Dynamixels
#define GRIPPER_ZERO_OFFSET -19968.0

// ---------------------- Timing ----------------------
#define LED_BLINK_INTERVAL 1000 /  10  // milliseconds
#define TIMEOUT_DURAITON 2000  // ms

// ---------------------- Pinout ----------------------
#define LIMIT_SWITCH_PIN 5
#define SOLENOID_PIN 29
#define STATUS_LIGHT_PIN 13 // Teensy onboard LED

#endif // CONSTANTS_H