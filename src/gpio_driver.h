/**
 * @file driver.h
 * @brief Public API for GPIO driver.
 *
 * Defines:
 * - Helper macros for bit manipulation
 * - Function prototypes for GPIO and interrupt configuration
 * - Button structure to hold information about the pin, port and whether it is active low/high
 *
 * Acts as the interface between application code and low-level driver logic.
 * 
 * Written by Edwin J Martinez
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "global.h"

//* GPIO Register Layout
typedef struct
{
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
} GPIORegisters;

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
    PULL_DOWN   = 0x2U
} PUPDMode;

typedef enum
{
    PUSH_PULL = 0U,
    OPEN_DRAIN
} OutputType;

typedef enum
{
    LOW_SPEED = 0U,
    MEDIUM_SPEED,
    HIGH_SPEED,
    FAST_SPEED
} OutputSpeed;

typedef struct 
{
    GPIORegisters* port;
    uint32_t pin;
    bool isActiveLow;
} Button;

//* Peripheral instances
#define GPIOA_REGS          ((GPIORegisters*) GPIOA_BASE)
#define GPIOB_REGS          ((GPIORegisters*) GPIOB_BASE)


/**
 * @brief Enables the peripheral clock for a given GPIO port.
 * 
 * @param port Bit position corresponding to the GPIO port in RCC_AHB1ENR.
 */
void enable_gpio_clock(uint32_t port);

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
void set_pin_by_odr(GPIORegisters* port, uint32_t pin);

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
void clear_pin_by_odr(GPIORegisters* port, uint32_t pin);

/**
 * @brief Clears a GPIO pin (sets it low) using BSRR (atomic write).
 * 
 * @param port Pointer to GPIO register structure.
 * @param pin Pin number within the GPIO port.
 */
void clear_pin_by_bsrr(GPIORegisters* port, uint32_t pin);

/**
 * @brief Toggles the output state of a GPIO pin using ODR (non-atomic).
 * 
 * @param port Pointer to GPIO register structure.
 * @param pin Pin number within the GPIO port.
 */
void toggle_pin_by_odr(GPIORegisters* port, uint32_t pin);

/**
 * @brief Reads the current logic level of a GPIO pin as a boolean value.
 * 
 * @param port Pointer to GPIO register structure.
 * @param pin Pin number within the GPIO port.
 * @return true if high, false if low.
 */
bool read_pin(GPIORegisters* port, uint32_t pin);

bool is_button_pressed(Button* btn);
