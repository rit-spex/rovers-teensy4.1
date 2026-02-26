#ifndef CONSTANTS_H
#define CONSTANTS_H

// which teensy are we on
#define TEENSY_ID 1

#if TEENSY_ID == 1

#define ENABLE_AUGER
#define ENABLE_SAMPLE_SLIDE
#define ENABLE_PUMPS

#elif TEENSY_ID == 2

#define ENABLE_SPECTROMETER
#define ENABLE_VIBRATOR

#endif

#define ENABLE_SERIAL 1

#define LED_BLINK_INTERVAL 500 // ms
#define UPDATE_RATE_MS 40
#define INIT_DELAY_MS 20

// Auger
#define AUGER_DRILL_SPEED 50
#define AUGER_DRILL_IDLE_SIGNAL 1500

// Sample Slide
// TODO: actual values
#define SS_COLLECTION1_POS 0
#define SS_COLLECTION2_POS 0
#define SS_PURGE_POS 0
#define SS_SAMPLE_CACHE_POS 0

// Pumps
#define NUM_PUMPS 3
// Currently all pumps use the same speed, but if you just construct Pump with
// a different speed it can be customized
#define PUMP_SPEED 0

#endif // CONSTANTS_H
