# --------------------------------------------------------------------
#                           SPEX ROVER 2025
# --------------------------------------------------------------------
# file name    : build.sh
# purpose      : run the makefile for each subsystem and copy thier files
# usage:
#  build         - build the current files in build folder
#  build arm     - build using the arm subsystem
#  build chassis - build using the chassis subsystem
#  build science - build using the science subsystem
#  build all     - build each subsystem
#  build clean   - cleans the bin and build folder
# created on   : 7/16/2025 - Tyler
# last modified: 7/16/2025 - Tyler
# --------------------------------------------------------------------

#!/bin/sh

# Globals
export TARGET_SUBSYSTEM="NONE"

# The different subsystems
arm_subsystem="arm"
chassis_subsystem="chassis"
science_subsystem="science"

# Functions
extract_subsystem_files()
{
    if [ $TARGET_SUBSYSTEM == "NONE" ]
    then
        echo "No active subsystem to build"
    else
        echo "Creating: "$TARGET_SUBSYSTEM

        # make the binary
        make

        # clean the build folder
        make clean
    fi
}

# Only build for current system
if [[ $1 == "" ]]
then
    extract_subsystem_files

# Only build for arm
elif [[ $1 == $arm_subsystem ]]
then
    TARGET_SUBSYSTEM=$arm_subsystem
    extract_subsystem_files

# Only build for chassis
elif [[ $1 == $chassis_subsystem ]]
then
    TARGET_SUBSYSTEM=$chassis_subsystem
    extract_subsystem_files

# Only build for science
elif [[ $1 == $science_subsystem ]]
then
    TARGET_SUBSYSTEM=$science_subsystem
    extract_subsystem_files

# Only build for all subsystems
elif [[ $1 == "all" ]]
then
    TARGET_SUBSYSTEM=$arm_subsystem
    extract_subsystem_files

    TARGET_SUBSYSTEM=$chassis_subsystem
    extract_subsystem_files

    TARGET_SUBSYSTEM=$science_subsystem
    extract_subsystem_files

# Only build for all subsystems
elif [ $1 == "clean" ]
then
    echo "Clean bin and build folder"
fi

