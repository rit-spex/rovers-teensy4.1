// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : Printer.cpp
// purpose      : to print the real time data of the process
// created on   : 8/13/2025 - Tyler
// last modified: 8/13/2025 - Tyler
// --------------------------------------------------------------------

#include "Printer.h"
#include <filesystem>
#include <fstream>
#include <stdlib.h>
#include <string>

// the number of chars in a line, this includes \n
#define NUMBER_OF_LINES 20

void createDataDir()
{
    std::filesystem::path dirPath = DATA_DIR;
    if (!std::filesystem::exists(dirPath))
    {
        std::filesystem::create_directories(dirPath);
    }
}

void clearFile()
{
    createDataDir();
    std::string filePath = std::string(DATA_DIR) + "/" + std::string(OUTPUT_FILE_NAME);

    FILE *fptr = NULL;

    // open or create the file
    fptr = fopen(filePath.c_str(), "w");

    // print 20 blank lines that are 20 char long
    for (int lineIdx = 0; lineIdx < NUMBER_OF_LINES; lineIdx++)
    {
        fprintf(fptr, ",\n");
    }

    // close the file at the end so data shouldn't be lost if program fails
    fclose(fptr);
}

// create the file then write at specified location then close file
void updateFile(PrinterData type, int extra, int value)
{
    createDataDir();
    FILE *newfptr = NULL;
    FILE *oldfptr = NULL;
    char *line = NULL;
    int lineIdx = 0;
    int lineSize;
    size_t size = 0;

    // open or create the file
    newfptr = fopen("tmp", "w");

    std::string filePath = std::string(DATA_DIR) + "/" + std::string(OUTPUT_FILE_NAME);
    // open or create the file
    oldfptr = fopen(filePath.c_str(), "r");

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
    remove(filePath.c_str());

    // rename the new file
    rename("tmp", filePath.c_str());
}
