/**
 * @file usart_driver.h
 * @brief 
 *
 * 
 * Written by Edwin J Martinez
 */

#pragma once
#include <stdint.h>

//* USART Register Layout
typedef struct
{
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
} UARTRegisters;

//* USART2 instances
#define USART2_REGS         ((UARTRegisters*) USART2_BASE)


/**
 * @brief Initializes USART2 for UART communication.
 * For the Nucleo-F446RE, USART2 is commonly connected to the ST-Link virtual COM port.
 *
 * @param baudRate Baud rate such as 9600 or 115200.
*/
void uart2_init(uint32_t baudRate);

/**
 * @brief Writes one byte through USART2.
 *
 * @param byte Byte to transmit.
*/
void uart2_write_byte(uint8_t byte);

/**
 * @brief Writes a null-terminated string through USART2.
 *
 * @param str String to transmit.
*/
void uart2_write_string(const char* str);
