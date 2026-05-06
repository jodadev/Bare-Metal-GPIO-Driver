/**
 * @file i2c_driver.h
 * @brief 
 *
 * 
 * Written by Edwin J Martinez
 */

#pragma once

#include <stdint.h>

typedef struct
{
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t OAR1;
    volatile uint32_t OAR2;
    volatile uint32_t DR;
    volatile uint32_t SR1;
    volatile uint32_t SR2;
    volatile uint32_t CCR;
    volatile uint32_t TRISE;
    volatile uint32_t FLTR;
} I2CRegisters;

#define I2C1_REGS           ((I2CRegisters*) I2C1_BASE)

/**
 * @brief Initializes the I2C1 peripheral and its GPIO pins.
 * Configures PB8 as I2C1_SCL and PB9 as I2C1_SDA using alternate function AF4.
 * The pins are configured as open-drain with pull-ups and fast speed.
 *
 * This function also enables the I2C1 peripheral clock and configures I2C1
 * for standard mode communication at 100 kHz.
*/
void i2c_init(void);

/**
 * @brief Writes one byte of data to a register on an I2C slave device.
 *
 * This function generates a START condition, sends the slave address in write mode,
 * sends the target register address, writes the data byte, and then generates a STOP condition.
 *
 * @param i2c Pointer to the I2C peripheral register block.
 * @param slave_addr 7-bit I2C slave address.
 * @param reg_addr Register address inside the slave device.
 * @param data Data byte to write to the target register.
*/
void i2c_write_register(I2CRegisters* i2c, uint8_t slave_addr, uint8_t reg_addr, uint8_t data);

/**
 * @brief Reads one byte of data from a register on an I2C slave device.
 *
 * This function writes the target register address first, then generates a repeated START
 * condition and reads one byte from the slave device.
 *
 * @param i2c Pointer to the I2C peripheral register block.
 * @param slave_addr 7-bit I2C slave address.
 * @param reg_addr Register address inside the slave device.
 *
 * @return The byte read from the target register.
*/
uint8_t i2c_read_register(I2CRegisters* i2c, uint8_t slave_addr, uint8_t reg_addr);
