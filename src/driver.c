/**
 * @file driver.c
 * @brief Implementation of low-level GPIO driver functions.
 *
 * Contains register-level functions for:
 * - Enabling peripheral clocks
 * - Configuring GPIO modes and pull settings
 * - Basic GPIO operations (set, clear, toggle, read)
 * - Convenient button read function
 * 
 *  Written by Edwin J Martinez
 */

#include "driver.h"
#include "hardware.h"

void enable_gpio_clock(uint32_t port)
{
    RCC_REGS->AHB1ENR |= BIT(port);
    (void)RCC_REGS->AHB1ENR;
}

void set_gpio_mode(GPIORegisters* port, uint32_t pin, GPIOMode mode)
{
    port->MODER &= ~(TWO_BIT_WIDTH << SHIFT_BY_TWO(pin));
    port->MODER |= ((mode & TWO_BIT_WIDTH) << SHIFT_BY_TWO(pin));
}

void set_pupd_mode(GPIORegisters* port, uint32_t pin, PUPDMode mode)
{
    port->PUPDR &= ~(TWO_BIT_WIDTH << SHIFT_BY_TWO(pin));
    port->PUPDR |= ((mode & TWO_BIT_WIDTH) << SHIFT_BY_TWO(pin));
}

void set_pin_by_odr(GPIORegisters* port, uint32_t pin)
{
    port->ODR |= BIT(pin);
}

void set_pin_by_bsrr(GPIORegisters* port, uint32_t pin)
{
    port->BSRR = BIT(pin);
}

void clear_pin_by_odr(GPIORegisters* port, uint32_t pin)
{
    port->ODR &= ~BIT(pin);
}

void clear_pin_by_bsrr(GPIORegisters* port, uint32_t pin)
{
    port->BSRR = BIT(pin + 16U);
}

void toggle_pin_by_odr(GPIORegisters* port, uint32_t pin)
{
    port->ODR ^= BIT(pin);
}

bool read_pin(GPIORegisters* port, uint32_t pin)
{
    return (port->IDR & BIT(pin)) != 0U;
}

bool is_button_pressed(Button* btn)
{
    bool raw = read_pin( btn->port, btn->pin);
    return btn->isActiveLow ? !raw : raw;
}
