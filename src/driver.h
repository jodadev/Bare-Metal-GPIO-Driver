#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "hardware.h"

//* Helpers
#define BIT(p)              (0x01UL << (p))
#define SHIFT_BY_TWO(p)     ((p) * 0x02U)
#define TWO_BIT_WIDTH       0x3UL

typedef enum
{
    GPIOMODE_INPUT              = 0x0U,
    GPIOMODE_OUTPUT             = 0x1U,
    GPIOMODE_ALTERNATE_FUNCTION = 0x2U,
    GPIOMODE_ANALOG             = 0x3U
} GPIOMode;

typedef enum
{
    NONE        = 0x0U,
    PULL_UP     = 0x1U,
    PULL_DOWN   = 0x2U,
    REVERSE     = 0x3U
} PUPDMode;

/**
 * @brief Enables the peripheral clock for a given GPIO port.
 * 
 * @param port Bit position corresponding to the GPIO port in RCC_AHB1ENR.
 */
void enable_clock(uint32_t port);

/**
 * @brief Configures the mode of a GPIO pin (input, output, alternate, analog).
 * 
 * @param port Pointer to GPIO register structure.
 * @param pin Pin number within the GPIO port.
 * @param mode Desired mode from GPIOMode enum.
 */
void set_gpio_mode(GPIORegisters* port, uint32_t pin, GPIOMode mode);

/**
 * @brief Configures the pull-up or pull-down resistor for a GPIO pin.
 * 
 * @param port Pointer to GPIO register structure.
 * @param pin Pin number within the GPIO port.
 * @param mode Pull configuration from PUPDMode enum.
 */
void set_pupd_mode(GPIORegisters* port, uint32_t pin, PUPDMode mode);

/**
 * @brief Sets a GPIO pin high using ODR (read-modify-write, non-atomic).
 * 
 * @param port Pointer to GPIO register structure.
 * @param pin Pin number within the GPIO port.
 */
void set_pin(GPIORegisters* port, uint32_t pin);

/**
 * @brief Sets a GPIO pin high using BSRR (atomic write).
 * 
 * @param port Pointer to GPIO register structure.
 * @param pin Pin number within the GPIO port.
 */
void set_pin_by_bsrr(GPIORegisters* port, uint32_t pin);

/**
 * @brief Clears a GPIO pin (sets it low) using ODR (read-modify-write, non-atomic).
 * 
 * @param port Pointer to GPIO register structure.
 * @param pin Pin number within the GPIO port.
 */
void clear_pin(GPIORegisters* port, uint32_t pin);

/**
 * @brief Clears a GPIO pin (sets it low) using BSRR (atomic write).
 * 
 * @param port Pointer to GPIO register structure.
 * @param pin Pin number within the GPIO port.
 */
void clear_pin_by_bsrr(GPIORegisters* port, uint32_t pin);

/**
 * @brief Toggles the output state of a GPIO pin using ODR.
 * 
 * @param port Pointer to GPIO register structure.
 * @param pin Pin number within the GPIO port.
 */
void toggle_pin(GPIORegisters* port, uint32_t pin);

/**
 * @brief Reads the current logic level of a GPIO pin as a numeric value (0 or 1).
 * 
 * @param port Pointer to GPIO register structure.
 * @param pin Pin number within the GPIO port.
 * @return uint8_t 0 if low, 1 if high.
 */
uint8_t read_pin(GPIORegisters* port, uint32_t pin);

/**
 * @brief Reads the current logic level of a GPIO pin as a boolean value.
 * 
 * @param port Pointer to GPIO register structure.
 * @param pin Pin number within the GPIO port.
 * @return true if high, false if low.
 */
bool read_pin_as_boolean(GPIORegisters* port, uint32_t pin);
