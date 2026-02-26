# Rovers CAN library

## Contributing
When implementing a new message, you **must** make sure that:
- The message is added to the `MessageID` enum in `message_id.h` with an ID in
accordance with the interface document and named in SCREAMING_SNAKE_CASE.
- The struct for the message is added to a file in `include/CAN/messages`.
- The struct name is the PascalCase version of the message ID name with `Msg`
  appended to the end:
    - **Ex**: `MessageID::ENABLE_ARM` -> `struct EnableArmMsg`
