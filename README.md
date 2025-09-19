# Subsystem Code
This repo hosts all projects we use for our subsystems.
Each subsystem has their own project because each subsystem is on their own teensy.

This is flashed onto the teensy with [PlatformIO extension](https://platformio.org/) in vs code.

Below are ways I have tested to get the serial port to work in the VM it is not working yet and needs more work.

To flash the software onto the teensy in linux ensure that you have privileges over serial ports.
This can be done by run the command below:

```sudo adduser your_username dialout```

To get working you will need to added serial device from the VM.

# Style
The SPEX rovers code style guide can be found [here](https://docs.google.com/document/d/1t-4s67TyD6nIQa1lq93bUDrvFOaI-m0L0P6DAW0iCVA/edit?usp=sharing).
## clang-format
The C++ codebase uses clang-format to enforce style rules. If you're developing on linux or mac please install:
- [clang-format](https://clang.llvm.org/docs/ClangFormat.html)
- [pre-commit](https://pre-commit.com/)

After you've installed these, in the root directory of the project run:
```
pre-commit install
```

Whenever you commit, the pre-commit git hook will run clang-format to check your code formatting. If there are problems, clang-format will automatically reformat the code so just try to commit again.

