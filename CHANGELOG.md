# Change Log

# v0.1.1
- Updated RCC reg access to not be hardcoded and instead to use a `C struct` with its members as `uint32` since that is the memory layout.
- Clarified `ODR` functions by postfixing `_by_odr`.
- Clarified `enable_clock` function by renaming it to `enable_gpio_clock`.
- Removed the typo `REVERSE` from the `PUPDMode` enum.
- Removed duplicate function `read_pin_as_boolean` and changed the return type of `read_pin` from `uint8` to `boolean`.
- Created new struct, `Button`, to hold information:
    - **pin:** the pin number.
    - **port:** the port the pin is in. Its a pointer to the actual base address of the port.
    - **is active low:** whether the button is in active low or not to determine how to read the value.
- Removed the logical `NOT` electrical logic from the `read_pin_as_boolean` function call in main and replaced with new function `is_button_pressed` which accepts a `Button` and handles the logic within `driver`.

# v0.1.0
- Initial GPIO driver implementation
- Basic input/output support
