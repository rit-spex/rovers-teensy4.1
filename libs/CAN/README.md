# Rovers CAN library

## Contributing
When implementing a new message, you **must** make sure that:
- The message is added to the `MessageType` enum in `codec.h` with an ID in
accordance with the interface document and named in SCREAMING_SNAKE_CASE.
- The struct for the message is added to a file in `include/messages`.
- **If you are creating a new header file for your message(s)**, include the
generated header file at the top, which will have the name of your header file
with `_codec` appended to it.
    - **Ex**: for `include/messages/science.h` -> `#include
    ../../generated/messages/science_codec.h`
- The struct name is the PascalCase version of the message type name with `Msg`
  appended to the end:
    - **Ex**: `MessageType::ENABLE_ARM` -> `struct EnableArmMsg`

**THIS IS ALL REQUIRED FOR THE ENCODING/DECODING CODEGEN TO OPERATE CORRECTLY**
