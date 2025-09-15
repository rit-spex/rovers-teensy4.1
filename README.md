# Subsystem Code
This repo hosts all projects we use for our subsystems.
Each subsystem has their own project because each subsystem is on their own teensy.

This is flashed onto the teensy with platformIO extension in vs code
To flash the software onto the teensy in linux ensure that you have privaliages over serial ports
This can be done by run the command below
sudo adduser your_username dialout

To get working you will need to added serial device from the VM