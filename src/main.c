#include "driver.h"

#include <stdbool.h>

//* Pins
#define LED_PIN             0x00U
#define BTN_PIN             0x01U


void init()
{
    // Enable the clock for Port A
    enable_clock(GPIOAEN);

    // Set LED pin, MODER, to Output Mode
    set_gpio_mode(GPIOA_REGS, LED_PIN, GPIOMODE_OUTPUT);

    // Set Button Pin, MODER, to Input Mode
    set_gpio_mode(GPIOA_REGS, BTN_PIN, GPIOMODE_INPUT);

    // Set Button Pin, PUPDR, to Pull-Up Resistor
    set_pupd_mode(GPIOA_REGS, BTN_PIN, PULL_UP);

    // Set LED to off by default
    clear_pin_by_bsrr(GPIOA_REGS, LED_PIN);

}

int main()
{
    init();

    while (1)
    {
        // simple button press & hold to turn light on
        bool isButtonPressed = !read_pin_as_boolean(GPIOA_REGS, BTN_PIN);

        if (isButtonPressed)
            set_pin_by_bsrr(GPIOA_REGS, LED_PIN);
        else
            clear_pin_by_bsrr(GPIOA_REGS, LED_PIN);  
    }
    
}
