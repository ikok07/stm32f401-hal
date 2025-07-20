//
// Created by Kok on 7/17/25.
//

#include "../include/config/system_config.h"

void TIM2_IRQHandler () {
    HAL_TIM_IRQHandler(systemConfig.pTIMHandle);
}

void EXTI2_IRQHandler() {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
}

void USART1_IRQHandler() {
    HAL_USART_IRQHandler(systemConfig.pUSARTHandle);
}