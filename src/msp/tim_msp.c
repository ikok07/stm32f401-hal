//
// Created by Kok on 7/17/25.
//

#include "stm32f4xx_hal.h"
#include "system_config.h"

void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM2) {
        __HAL_RCC_TIM2_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();

        GPIO_InitTypeDef GPIO_Config = {
            .Alternate = GPIO_AF1_TIM2,
            .Mode = GPIO_MODE_AF_PP,
            .Pull = GPIO_PULLDOWN,
            .Speed = GPIO_SPEED_FREQ_LOW,
        };

        // Channel 1
        GPIO_Config.Pin = GPIO_PIN_0;
        HAL_GPIO_Init(GPIOA, &GPIO_Config);

        // Channel 2
        GPIO_Config.Pin = GPIO_PIN_1;
        HAL_GPIO_Init(GPIOA, &GPIO_Config);

        // Reset pin
        GPIO_Config.Mode = GPIO_MODE_IT_RISING;
        GPIO_Config.Pin = GPIO_PIN_2;
        GPIO_Config.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(GPIOA, &GPIO_Config);


        // Enable interrupts
        HAL_NVIC_SetPriority(EXTI2_IRQn, ENCODER_RESET_IRQ_PRIORITY, ENCODER_RESET_IRQ_PRIORITY);
        HAL_NVIC_SetPriority(TIM2_IRQn, ENCODER_TIM_IRQ_PRIORITY, ENCODER_TIM_IRQ_PRIORITY);
        HAL_NVIC_EnableIRQ(EXTI2_IRQn);
        HAL_NVIC_EnableIRQ(TIM2_IRQn);
    }
}
