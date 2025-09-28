// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : Printer.h
// purpose      : to print the real time data of the process
// created on   : 8/13/2025 - Tyler
// last modified: 8/13/2025 - Tyler
// --------------------------------------------------------------------
#ifndef PRINTER_H
#define PRINTER_H

#include "GlobalVars.h"
#include <stdio.h>

// the structure of the output file and sets the first line of each section
enum PrinterData
{
    PIN = 0
};

void createDataDir();

// creates an empty file
void clearFile();

// print the data to the file
void updateFile(PrinterData type, int extra, int value);

#endif // PRINTER_H
