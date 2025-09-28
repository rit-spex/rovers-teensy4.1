// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : GlobalVars.h
// purpose      : This file contains all data that need to be shared between simulated hardware
// created on   : 8/14/2025 - Tyler
// last modified: 8/14/2025 - Tyler
// --------------------------------------------------------------------

#ifndef GLOBAL_VARS_H
#define GLOBAL_VARS_H

#define DATA_DIR "data"

// get the file name based on what is being build
#if BUILD_CHASSIS
#define OUTPUT_FILE_NAME "chassisData.txt"

extern int pwm_pin_0;
extern int pwm_pin_1;
extern int pwm_pin_2;
extern int pwm_pin_3;
extern int pwm_pin_4;
extern int pwm_pin_5;
#elif BUILD_ARM
#define OUTPUT_FILE_NAME "armData.txt"
#elif BUILD_SCIENCE
#define OUTPUT_FILE_NAME "scienceData.txt"
#else
#error "No BUILD WAS SELECTED"
#endif

#endif // GLOBAL_VARS_H
