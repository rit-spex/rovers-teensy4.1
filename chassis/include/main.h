#include "Constants.h"
#include "DEBUG.h"

#include <Arduino.h>
#include <memory>

#if ENABLE_DEMO_ENCODER
#include "QuadDecoder.h"
#endif

// The drivebase is the main body board
#include "MainBodyBoard.h"

#if ENABLE_DEMO_ENCODER
// #define ENCODER_RUN_CYCLE_MICROSEC 1000
// IntervalTimer encoderTimer;
QuadratureDecoder demo_encoder{ENC_A_PIN_0, ENC_B_PIN_0};
#endif

// create the main body board
static unsigned long currentRunCycle = 0;
static std::shared_ptr<MainBodyBoard> mbb;
