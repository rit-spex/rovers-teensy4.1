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

#include <stdio.h>

// class Printer
// {
//     public:
//         // the structure of the output file and sets the first line of each section
//         enum PrinterData
//         {
//             PIN = 0
//         };

//         Printer();
//         void SetFile(char* fileName);
//         // print the data to the file
//         void PrintData(PrinterData type, int extra, int value);
//     private:
//         char* m_fileName;
// };

// // create a global reference
// static Printer printer = Printer();

// the structure of the output file and sets the first line of each section
enum PrinterData
{
    PIN = 0
};

#define OUTPUT_FILE_NAME "chassisData.txt"

void ClearFile();
// print the data to the file
void PrintData(PrinterData type, int extra, int value);
//char* m_fileName;

// create a global reference
// static Printer printer = Printer();

#endif // PRINTER_H