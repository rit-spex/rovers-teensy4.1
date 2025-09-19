The simulator is designed to allow developers to run the hardware without actually having the devices
The simulator simulates the CANBus and the Xbee with UDP packets. 

To build the simulated exec run (each command will build different components)
./build chassis
./build arm
./build science
./build all

These will build an executable that will be in the /bin folder
