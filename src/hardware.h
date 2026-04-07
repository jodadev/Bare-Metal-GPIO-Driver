#pragma once

#include <stdint.h>

//* Base Addresses
#define PERIPH_BASE         0x40000000UL
#define AHB1_BASE           (PERIPH_BASE + 0x00020000UL)
#define RCC_BASE            (AHB1_BASE   + 0x00003800UL)
#define GPIOA_BASE          (AHB1_BASE   + 0x00000000UL)

//* Offsets
#define RCC_AHB1ENR_OFFSET  0x30UL

//* RCC clock bits
#define GPIOAEN             0x00U

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

//* Peripheral instances
#define GPIOA_REGS          ((GPIORegisters*)GPIOA_BASE)

//* RCC register
#define RCC_AHB1ENR         (*(volatile uint32_t*)(RCC_BASE + RCC_AHB1ENR_OFFSET))
