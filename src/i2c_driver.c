/**
 * @file i2c_driver.c
 * @brief 
 *
 * 
 * Written by Edwin J Martinez
 */

#include "i2c_driver.h"
#include "gpio_driver.h"
#include "global.h"
#include "hardware.h"

#define SDA_PIN             0x08U // D15 -> PB8
#define SCL_PIN             0x09U // D14 -> PB9

/**
 * @brief Generates an I2C START condition.
 *
 * This function sets the START bit in CR1 and waits until the SB flag is set,
 * indicating that the START condition has been generated.
 *
 * @param i2c Pointer to the I2C peripheral register block.
*/
static void i2c_start(I2CRegisters* i2c)
{
    // Generate START
    i2c->CR1 |= (1U << 8);

    // Wait until START condition generated (SB = 1)
    while (!(i2c->SR1 & (1U << 0)))
    {
    }
}

/**
 * @brief Sends the I2C slave address in write mode.
 *
 * This function writes the 7-bit slave address with the write bit cleared,
 * waits for the ADDR flag, and clears the ADDR flag by reading SR1 followed by SR2.
 *
 * @param i2c Pointer to the I2C peripheral register block.
 * @param slave_addr 7-bit I2C slave address.
*/
static void i2c_send_address_write(I2CRegisters* i2c, uint8_t slave_addr)
{
    i2c->DR = (slave_addr << 1);

    // Wait for ADDR flag
    while (!(i2c->SR1 & (1U << 1)))
    {
    }

    // Clear ADDR by reading SR1 then SR2
    volatile uint32_t temp = i2c->SR1;
    temp = i2c->SR2;
    (void)temp;
}

/**
 * @brief Sends the I2C slave address in read mode.
 *
 * This function writes the 7-bit slave address with the read bit set,
 * waits for the ADDR flag, and clears the ADDR flag by reading SR1 followed by SR2.
 *
 * @param i2c Pointer to the I2C peripheral register block.
 * @param slave_addr 7-bit I2C slave address.
*/
static void i2c_send_address_read(I2CRegisters* i2c, uint8_t slave_addr)
{
    i2c->DR = (slave_addr << 1) | 1U;

    // Wait for ADDR flag
    while (!(i2c->SR1 & (1U << 1)))
    {
    }

    // Clear ADDR by reading SR1 then SR2
    volatile uint32_t temp = i2c->SR1;
    temp = i2c->SR2;
    (void)temp;
}

/**
 * @brief Writes one byte to the I2C data register.
 *
 * This function waits until the transmit data register is empty, writes the byte,
 * and then waits until the byte transfer is finished.
 *
 * @param i2c Pointer to the I2C peripheral register block.
 * @param data Data byte to transmit.
*/
static void i2c_write_byte(I2CRegisters* i2c, uint8_t data)
{
    // Wait until data register empty
    while (!(i2c->SR1 & (1U << 7)))   // TXE
    {
    }

    i2c->DR = data;

    // Wait until byte transfer finished
    while (!(i2c->SR1 & (1U << 2)))   // BTF
    {
    }
}

/**
 * @brief Generates an I2C STOP condition.
 *
 * This function sets the STOP bit in CR1 to release the I2C bus.
 *
 * @param i2c Pointer to the I2C peripheral register block.
*/
static void i2c_stop(I2CRegisters* i2c)
{
    i2c->CR1 |= (1U << 9);
}



void i2c_write_register(I2CRegisters* i2c, uint8_t slave_addr, uint8_t reg_addr, uint8_t data)
{
    // 1. START
    i2c_start(i2c);

    // 2. Send slave address + WRITE
    i2c_send_address_write(i2c, slave_addr);

    // 3. Send register address
    i2c_write_byte(i2c, reg_addr);

    // 4. Send data
    i2c_write_byte(i2c, data);

    // 5. STOP
    i2c_stop(i2c);
}

uint8_t i2c_read_register(I2CRegisters* i2c, uint8_t slave_addr, uint8_t reg_addr)
{
    uint8_t data;

    // 1. Make sure ACK is enabled before beginning
    i2c->CR1 |= (1U << 10);

    // 2. START
    i2c_start(i2c);

    // 3. Send slave address + WRITE
    i2c_send_address_write(i2c, slave_addr);

    // 4. Send register address
    i2c_write_byte(i2c, reg_addr);

    // 5. REPEATED START
    i2c_start(i2c);

    // 6. Disable ACK because we only want 1 byte
    i2c->CR1 &= ~(1U << 10);

    // 7. Send slave address + READ
    i2c->DR = (slave_addr << 1) | 1U;

    // 8. Wait for ADDR
    while (!(i2c->SR1 & (1U << 1)))
    {
    }

    // 9. Clear ADDR by reading SR1 then SR2
    volatile uint32_t temp = i2c->SR1;
    temp = i2c->SR2;
    (void)temp;

    // 10. Generate STOP immediately after clearing ADDR
    i2c->CR1 |= (1U << 9);

    // 11. Wait until receive buffer not empty
    while (!(i2c->SR1 & (1U << 6)))   // RXNE
    {
    }

    // 12. Read received byte
    data = (uint8_t)i2c->DR;

    // 13. Re-enable ACK for future reads
    i2c->CR1 |= (1U << 10);

    return data;
}

void i2c_init(void)
{
    //* GPIO INIT
    // 1. Enable GPIOB clock
    enable_gpio_clock(GPIOBEN);

    // 2. Set PB8 and PB9 to alternate function mode
    set_gpio_mode(GPIOB_REGS, SCL_PIN, GPIOMODE_ALTERNATE_FUNCTION);
    set_gpio_mode(GPIOB_REGS, SDA_PIN, GPIOMODE_ALTERNATE_FUNCTION);

    // 3. Set PB8 and PB9 as open-drain
    GPIOB_REGS->OTYPER |= (OPEN_DRAIN << SCL_PIN) | (OPEN_DRAIN << SDA_PIN);
    // GPIOB_REGS->OTYPER |= (OPEN_DRAIN << SDA_PIN);
    
    // 4. Set pull-up
    set_pupd_mode(GPIOB_REGS, SCL_PIN, PULL_UP);
    set_pupd_mode(GPIOB_REGS, SDA_PIN, PULL_UP);
    
    // 5. Set high speed
    GPIOB_REGS->OSPEEDR &= ~((TWO_BIT_WIDTH << SHIFT_BY_TWO(SCL_PIN)) | (TWO_BIT_WIDTH << SHIFT_BY_TWO(SDA_PIN)));
    GPIOB_REGS->OSPEEDR |= ((TWO_BIT_WIDTH & FAST_SPEED) << SHIFT_BY_TWO(SCL_PIN)) | ((TWO_BIT_WIDTH & FAST_SPEED) << SHIFT_BY_TWO(SDA_PIN));

    // 6. Select AF4 for PB8 and PB9
    GPIOB_REGS->AFR[1] &= ~((FOUR_BIT_WIDTH << SHIFT_BY_FOUR((SCL_PIN - 8U))) | (FOUR_BIT_WIDTH << SHIFT_BY_FOUR((SDA_PIN - 8U))));
    GPIOB_REGS->AFR[1] |= ((FOUR_BIT_WIDTH & 0x04) << SHIFT_BY_FOUR((SCL_PIN - 8U))) | ((FOUR_BIT_WIDTH & 0x04) << SHIFT_BY_FOUR((SDA_PIN - 8U)));

    //* I2C INIT
    // 1. Enable I2C1 clock
    RCC_REGS->APB1ENR |= BIT(I2C1EN);
    (void)RCC_REGS->APB1ENR;

    // 2. Disable I2C before configuration
    I2C1_REGS->CR1 &= ~(BIT(0));

    // 3. Set peripheral clock frequency in MHz
    // Since APB1 = 16 MHz, we set FREQ = 16
    I2C1_REGS->CR2 = 16U;

    // 4. Set clock control register for 100 kHz standard mode
    // CCR = 80 for 100 kHz when PCLK1 = 16 MHz
    I2C1_REGS->CCR = 80U;

    // 5. Set maximum rise time
    // TRISE = FREQ + 1 for standard mode
    I2C1_REGS->TRISE = 17U;

    // 6. Enable I2C
    I2C1_REGS->CR1 |= BIT(0);
}
