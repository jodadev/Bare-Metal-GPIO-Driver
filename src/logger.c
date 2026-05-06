/**
 * @file logger.c
 * @brief Logging via USART to PC monitor.
 *
 * 
 * Written by Edwin J Martinez
 */

#include <stdbool.h>
#include "logger.h"
#include "hardware.h"
#include "gpio_driver.h"
#include "usart_driver.h"
#include "global.h"


static int convert_to_number(char ch)
{
    return ((int)ch) - 48;
}

static char convert_to_character(int num)
{
    return  (char)(48 + num);
}

static bool is_number(char ch)
{
    return ((int)ch) >= 48 && ((int)ch) < 58;
}

void init_logging(uint32_t baudRate)
{
    uart2_init(baudRate);
}

void prints(char str[], ...)
{
    va_list args;
    va_start(args, str);

    // Simple Parser
    char ch = ' ';
    int ith = 0;

    while (ch != '\0')
    {
        ch = str[ith];
        
        if (ch == '%')
        {
            ch = str[++ith]; // consume '%' and move to the next character
            switch (ch)
            {
            case 'd': // Integer Formating
            {
                volatile int val = va_arg(args, int); // extract arg
                char numBuffer[32];
                for (int i = 0; i < 32; i++) numBuffer[i] = ' ';
                
                // extract each digit from val and place in reverse in buffer - this way we can read correctly
                int index = 31;
                bool ok = true;
                while (val > 0)
                {
                    int digit = val % 10;   // this part extracts the digit to the right - does NOT remove it
                    val /= 10;              // this part removes the digit to the right

                    numBuffer[index--] = convert_to_character(digit); // we convert digit to character and place in the buffer. decrement after.
                    if (index < 0) ok = false; // ensure we do not go negative
                }

                if (!ok) continue; // hit an error, so we just continue and drop this value from being parsed

                // iterate the buffer and flush to uart_write to display the number
                index = 0;
                char numCh = numBuffer[index];
                while (numCh != '\0')
                {
                    if (is_number(numCh))
                        uart2_write_byte((uint8_t)numCh);
                    numCh = numBuffer[index++];
                }
            }
                break;
            
            case 's': // String Formating
            {
                volatile const char* val = va_arg(args, char*); // extract arg
                for(int i = 0; val[i] != '\0'; i++)
                    uart2_write_byte((uint8_t)val[i]);
            }
                break;
            }
        }
        else
        {
            uart2_write_byte((uint8_t)str[ith]);
        }
        
        ith++;
    }

    va_end(args);
}
