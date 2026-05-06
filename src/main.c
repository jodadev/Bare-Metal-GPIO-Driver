/**
 * @file main.c
 * @brief Application entry point demonstrating driver interaction.
 *
 *
 * Behavior:
 * - Polls a I2C device's ID.
 * - Logs this ID to the console on PC via USART/ST-Link.
 *
 * Written by Edwin J Martinez
 */

#include "hardware.h"
#include "i2c_driver.h"
#include "logger.h"
#include <stdbool.h>

int main()
{

    init_logging(115200);

    i2c_init();

    // Wake up MPU6050 (MPU6050's address is 0x68. Its reset register address is 0x6B and we just send empty data 0x00)
    i2c_write_register(I2C1_REGS, 0x68, 0x6B, 0x00);

    // Read identity register (MPU6050's address is 0x68 and its WHO_AM_I register is at 0x75)
    uint8_t id = i2c_read_register(I2C1_REGS, 0x68, 0x75);

    while (1)
    {

        for (volatile uint32_t i = 0; i < 500000; i++) {} // simple delay so printing is not spammed
        prints("I2C MPU-6050 device id: %d\r\n", id);
    }
    
}
