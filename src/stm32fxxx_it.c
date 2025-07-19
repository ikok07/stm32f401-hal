//
// Created by Kok on 7/17/25.
//

#include "system_config.h"

void SysTick_Handler() {
    HAL_IncTick();
    HAL_SYSTICK_IRQHandler();
}

void TIM2_IRQHandler () {
    HAL_TIM_IRQHandler(systemConfig.pTIMHandle);
}

void EXTI2_IRQHandler() {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
}
