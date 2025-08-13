// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : Printer.cpp
// purpose      : to print the real time data of the process
// created on   : 8/13/2025 - Tyler
// last modified: 8/13/2025 - Tyler
// --------------------------------------------------------------------

#include "Printer.h"

// the number of chars in a line, this includes \n
#define CHAR_PER_LINE 20
#define NUMBER_OF_LINES 20

// Printer::Printer()
// {
//     m_fileName = "";
// }

void ClearFile()
{
    FILE* fptr;

    // open or create the file
    fptr = fopen(OUTPUT_FILE_NAME, "w+");

    // print 20 blank lines that are 20 char long
    for(int lineIdx = 0; lineIdx<NUMBER_OF_LINES; lineIdx++)
    {
        for(int charIdx = 0; charIdx<CHAR_PER_LINE-1; charIdx++)
        {
            fprintf(fptr, " ");
        }
        fprintf(fptr, "\n");
    }

    // close the file at the end so data shouldn't be lost if program fails
    fclose(fptr);    
}

// create the file then write at specified location then close file
void PrintData(PrinterData type, int extra, int value)
{    
    FILE* fptr;

    // open or create the file
    fptr = fopen(OUTPUT_FILE_NAME, "aw+");

    // move to the section
    fseek(fptr, (extra + type) * CHAR_PER_LINE + 1, SEEK_SET);

    // insert the value
    fprintf(fptr, "%d", value);

    // close the file at the end so data shouldn't be lost if program fails
    fclose(fptr);
}