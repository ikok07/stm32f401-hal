//
// Created by Kok on 7/17/25.
//

#include "stm32f4xx_hal_cortex.h"
#include "../lib/stm32f4xx-hal-driver/Inc/stm32f4xx_hal.h"

void SysTick_Handler() {
    HAL_IncTick();
    HAL_SYSTICK_IRQHandler();
}
