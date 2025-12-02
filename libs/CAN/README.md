# Rovers CAN library

## Contributing
When implementing a new message, you **must** make sure that:
- The message is added to the `MessageType` enum in `message_types.h` with an ID in
accordance with the interface document and named in SCREAMING_SNAKE_CASE.
- The struct for the message is added to a file in `include/CAN/messages`.
- The struct name is the PascalCase version of the message type name with `Msg`
  appended to the end:
    - **Ex**: `MessageType::ENABLE_ARM` -> `struct EnableArmMsg`
