// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : Printer.cpp
// purpose      : to print the real time data of the process
// created on   : 8/13/2025 - Tyler
// last modified: 8/13/2025 - Tyler
// --------------------------------------------------------------------

#include "Printer.h"
#include <stdlib.h>

// the number of chars in a line, this includes \n
#define NUMBER_OF_LINES 20

void ClearFile()
{
    FILE *fptr;

    // open or create the file
    fptr = fopen(OUTPUT_FILE_NAME, "w");

    // print 20 blank lines that are 20 char long
    for (int lineIdx = 0; lineIdx < NUMBER_OF_LINES; lineIdx++)
    {
        fprintf(fptr, ",\n");
    }

    // close the file at the end so data shouldn't be lost if program fails
    fclose(fptr);
}

// create the file then write at specified location then close file
void UpdateFile(PrinterData type, int extra, int value)
{
    FILE *newfptr = NULL;
    FILE *oldfptr = NULL;
    char *line = NULL;
    int lineIdx = 0;
    int lineSize;
    size_t size = 0;

    // open or create the file
    newfptr = fopen("tmp", "w");

    // open or create the file
    oldfptr = fopen(OUTPUT_FILE_NAME, "r");

    // copy each line to the new file
    while ((lineSize = getline(&line, &size, oldfptr)) != -1)
    {
        if (lineIdx == (extra + type))
        {
            if (type == PrinterData::PIN)
            {
                fprintf(newfptr, "PIN:%d Value:%d,\n", extra, value);
            }
            else
            {
                fprintf(newfptr, "%d,\n", value);
            }
        }
        else
        {
            fprintf(newfptr, "%s", line);
        }
        lineIdx++;
    }

    free(line);
    // close the file at the end so data shouldn't be lost if program fails
    fclose(newfptr);
    fclose(oldfptr);

    // remove the old file
    remove(OUTPUT_FILE_NAME);

    // rename the new file
    rename("tmp", OUTPUT_FILE_NAME);
}
