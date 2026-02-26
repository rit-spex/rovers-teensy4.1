#ifndef PINOUT_H
#define PINOUT_H

#define STATUS_LIGHT_PIN 13

// Auger
#define AUGER_TIC_ADDR 0x0E
#define AUGER_DRILL_MOTOR_PIN 7

// Sample Slide
#define SS_TIC_ADDR 0x0F

// Pump
#define PUMP_0_ADDR 0x09
#define PUMP_1_ADDR 0x0A
#define PUMP_2_ADDR 0x0B
#define PUMP_3_ADDR 0x0C
// Currently all pumps use the same speed, but if you just construct Pump with
// a different speed it can be customized

#endif // PINOUT_H
