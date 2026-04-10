/**
 * @file main.c
 * @brief Application entry point demonstrating driven GPIO handling.
 *
 * Configures:
 * - GPIO for LED output and button input
 *
 * Behavior:
 * - Button press while polling
 * - While pressed, set LED on, else, off
 *
 * Written by Edwin J Martinez
 */

#include "driver.h"

#include <stdbool.h>

//* Pins
#define LED_PIN             0x00U

Button g_Button = 
{
    port:           GPIOA_REGS,
    pin:            0x01U,
    isActiveLow:    true
};


void init()
{
    // Enable the clock for Port A
    enable_gpio_clock(GPIOAEN);

    // Set LED pin, MODER, to Output Mode
    set_gpio_mode(GPIOA_REGS, LED_PIN, GPIOMODE_OUTPUT);

    // Set Button Pin, MODER, to Input Mode
    set_gpio_mode(GPIOA_REGS, g_Button.pin, GPIOMODE_INPUT);

    // Set Button Pin, PUPDR, to Pull-Up Resistor
    set_pupd_mode(GPIOA_REGS, g_Button.pin, PULL_UP);

    // Set LED to off by default
    clear_pin_by_bsrr(GPIOA_REGS, LED_PIN);

}

int main()
{
    init();

    while (1)
    {
        // simple button press & hold to turn light on
        bool isButtonPressed = is_button_pressed(&g_Button);

        if (isButtonPressed)
            set_pin_by_bsrr(GPIOA_REGS, LED_PIN);
        else
            clear_pin_by_bsrr(GPIOA_REGS, LED_PIN);  
    }
    
}
