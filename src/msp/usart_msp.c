//
// Created by Kok on 7/17/25.
//

#include "stm32f4xx_hal.h"

void HAL_USART_MspInit(USART_HandleTypeDef *husart) {
    GPIO_InitTypeDef GPIO_Config = {
        .Mode = GPIO_MODE_AF_PP,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_FAST,
    };

    if (husart->Instance == USART1) {
        GPIO_Config.Alternate = GPIO_AF7_USART1;
        GPIO_Config.Pin = GPIO_PIN_9;

        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_USART1_CLK_ENABLE();

        // init TX Pin
        HAL_GPIO_Init(GPIOA, &GPIO_Config);

        GPIO_Config.Pin = GPIO_PIN_10;

        // Init RX Pin
        HAL_GPIO_Init(GPIOA, &GPIO_Config);
    } else if (husart->Instance == USART2) {
        GPIO_Config.Alternate = GPIO_AF7_USART2;
        GPIO_Config.Pin = GPIO_PIN_2;

        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_USART2_CLK_ENABLE();

        // init TX Pin
        HAL_GPIO_Init(GPIOA, &GPIO_Config);

        GPIO_Config.Pin = GPIO_PIN_3;

        // Init RX Pin
        HAL_GPIO_Init(GPIOA, &GPIO_Config);
    } else if (husart->Instance == USART6) {
        GPIO_Config.Alternate = GPIO_AF8_USART6;
        GPIO_Config.Pin = GPIO_PIN_11;

        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_USART6_CLK_ENABLE();

        // init TX Pin
        HAL_GPIO_Init(GPIOA, &GPIO_Config);

        GPIO_Config.Pin = GPIO_PIN_12;

        // Init RX Pin
        HAL_GPIO_Init(GPIOA, &GPIO_Config);
    }
}
