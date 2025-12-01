# Subsystem Code
This repo hosts all projects we use for our subsystems.
Each subsystem has their own project because each subsystem is on their own teensy.

This is flashed onto the teensy with [PlatformIO extension](https://platformio.org/) in vs code.

Below are ways I have tested to get the serial port to work in the VM it is not working yet and needs more work.

To flash the software onto the teensy in linux ensure that you have privileges over serial ports.
This can be done by run the command below:

```sudo adduser your_username dialout```

To get working you will need to added serial device from the VM.

TO setup git submodules and also install the code style tools on Ubuntu, run:
```
./scripts/setup.sh
```

# Style
The SPEX rovers code style guide can be found [here](https://docs.google.com/document/d/1t-4s67TyD6nIQa1lq93bUDrvFOaI-m0L0P6DAW0iCVA/edit?usp=sharing).

## clang-format
The C++ codebase uses clang-format to enforce style rules.

To format the codebase, run:
```
./scripts/format.sh
```
## clang-tidy & cppcheck
The codebase can (VERY JANKILY) use clang-tidy and cppcheck for static code analysis.

To use it, navigate to a subsystem directory and run:
```
pio check
```

Or, to check all subsystems, run:
```
./scripts/tidy.sh
```

## codecov setup 
This is used to see the code coverage