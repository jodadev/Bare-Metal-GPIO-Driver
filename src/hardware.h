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
#define RCC_BASE            (AHB1_BASE   + 0x00003800UL)
#define GPIOA_BASE          (AHB1_BASE   + 0x00000000UL)

//* RCC clock bits
#define GPIOAEN             0x00U
#define GPIOBEN             0x01U
#define GPIOCEN             0x02U
#define GPIODEN             0x03U
#define GPIOEEN             0x04U
#define GPIOFEN             0x05U
#define GPIOGEN             0x06U
#define GPIOHEN             0x07U

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

//* Peripheral instances
#define GPIOA_REGS          ((GPIORegisters*) GPIOA_BASE)

//* RCC instances
#define RCC_REGS            ((RCCRegisters*) RCC_BASE)
