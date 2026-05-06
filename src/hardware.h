/**
 * @file hardware.h
 * @brief Hardware register definitions and memory mappings for STM32.
 *
 * Contains:
 * - Base addresses for peripherals (GPIO, RCC)
 * - GPIO register structure definition
 * - RCC register structure definition
 * - Enums for GPIO modes and ports
 * 
 * Written by Edwin J Martinez
 */

#pragma once

#include <stdint.h>

//* Base Addresses
#define PERIPH_BASE         0x40000000UL
#define AHB1_BASE           (PERIPH_BASE + 0x00020000UL)
#define APB1_BASE           (PERIPH_BASE + 0x00000000UL)
#define RCC_BASE            (AHB1_BASE   + 0x00003800UL)
#define GPIOA_BASE          (AHB1_BASE   + 0x00000000UL)
#define GPIOB_BASE          (AHB1_BASE   + 0x00000400UL)
#define USART2_BASE         (APB1_BASE   + 0x00004400UL)
#define I2C1_BASE           (APB1_BASE   + 0x00005400UL)

#define SYS_FREQ            16000000
#define APB1_CLK            (SYS_FREQ)

//* RCC clock bits
#define GPIOAEN             0x00U
#define GPIOBEN             0x01U
#define GPIOCEN             0x02U
#define GPIODEN             0x03U
#define GPIOEEN             0x04U
#define GPIOFEN             0x05U
#define GPIOGEN             0x06U
#define GPIOHEN             0x07U
#define I2C1EN              0x15U // 0001 0101
#define I2C2EN              0x16U
#define I2C3EN              0x17U

//* RCC Register Layout
typedef struct
{
    volatile uint32_t CR;
    volatile uint32_t PLL;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;
    volatile uint32_t AHB3RSTR;
    volatile uint32_t DUMMY_1;
    volatile uint32_t APB1RSTR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t DUMMY_2[2];
    volatile uint32_t AHB1ENR;
    volatile uint32_t AHB2ENR;
    volatile uint32_t AHB3ENR;
    volatile uint32_t DUMMY_3;
    volatile uint32_t APB1ENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t DUMMY_4[2];
    volatile uint32_t AHB1LPENR;
    volatile uint32_t AHB2LPENR;
    volatile uint32_t AHB3LPENR;
    volatile uint32_t DUMMY_5;
    volatile uint32_t APB1LPENR;
    volatile uint32_t APB2LPENR;
    volatile uint32_t DUMMY_6[2];
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
    volatile uint32_t DUMMY_7[2];
    volatile uint32_t SSCGR;
    volatile uint32_t PLLI2SCFGR;
    volatile uint32_t PLLSAICFGR;
    volatile uint32_t DCKCFGR;
    volatile uint32_t CKGATENR;
    volatile uint32_t DCKCFGR2;
} RCCRegisters;

//* RCC instances
#define RCC_REGS            ((RCCRegisters*) RCC_BASE)
