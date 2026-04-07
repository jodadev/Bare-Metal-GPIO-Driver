#include "driver.h"
#include "hardware.h"

void enable_clock(uint32_t port)
{
    RCC_AHB1ENR |= BIT(port);
    (void)RCC_AHB1ENR;
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

void set_pin(GPIORegisters* port, uint32_t pin)
{
    port->ODR |= BIT(pin);
}

void set_pin_by_bsrr(GPIORegisters* port, uint32_t pin)
{
    port->BSRR = BIT(pin);
}

void clear_pin(GPIORegisters* port, uint32_t pin)
{
    port->ODR &= ~BIT(pin);
}

void clear_pin_by_bsrr(GPIORegisters* port, uint32_t pin)
{
    port->BSRR = BIT(pin + 16U);
}

void toggle_pin(GPIORegisters* port, uint32_t pin)
{
    port->ODR ^= BIT(pin);
}

uint8_t read_pin(GPIORegisters* port, uint32_t pin)
{
    return (port->IDR & BIT(pin)) ? 1U : 0U;
}

bool read_pin_as_boolean(GPIORegisters* port, uint32_t pin)
{
    return (port->IDR & BIT(pin)) != 0U;
}
