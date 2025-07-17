
#include <stdio.h>

#include "stm32f4xx_hal.h"

USART_HandleTypeDef husart = {
    .Instance = USART1,
    .Init = {
        .Mode = USART_MODE_TX,
        .BaudRate = 9600,
        .Parity = USART_PARITY_NONE,
        .StopBits = USART_STOPBITS_1,
        .WordLength = USART_WORDLENGTH_8B,
    }
};

int __io_putchar(int ch) {
    HAL_USART_Transmit(&husart, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line) {
    while (1);
}

#endif

int main(void) {
    if (HAL_Init() != HAL_OK) {
        while (1);
    }

    if (HAL_USART_Init(&husart) != HAL_OK) {
        while (1);
    }

    printf("Hello, World!\n");

    return 0;
}