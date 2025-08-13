#include "../include/Constants.h"
#include "../include/DEBUG.h"

#if ENABLE_DEMO_ENCODER
#include "../include/QuadDecoder.h"
#endif

// the simulator will emulate the hardware
#if ENABLE_SIMULATOR
#include "../TestSystem/Simulator.h"
#else
#include <Arduino.h>
#endif

// The drivebase is the main body board
#include "../include/MainBodyBoard.h"

#if ENABLE_DEMO_ENCODER
// #define ENCODER_RUN_CYCLE_MICROSEC 1000
// IntervalTimer encoderTimer;
QuadratureDecoder demo_encoder{ENC_A_PIN_0, ENC_B_PIN_0};
#endif

// create the main body board
static unsigned long currentRunCycle = 0;
static MainBodyBoard* mbb;
