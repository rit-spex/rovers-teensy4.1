// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : arduinoMain.h
// purpose      : calls the setup and loop functions that arduino uses
// created on   : 7/30/2025 - Tyler
// last modified: 7/30/2025 - Tyler
// --------------------------------------------------------------------

#include "main.h"

#include "Printer.h"

#include <iostream>

CANbus ACAN_T4::can1;
CANbus ACAN_T4::can2;
CANbus ACAN_T4::can3;

extern void setup();
extern void loop();

int main()
{
    ClearFile();
    setup();
    while(true)
    {
        loop();
    }
}