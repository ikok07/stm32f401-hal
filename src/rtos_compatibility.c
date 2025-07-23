//
// Created by Kok on 7/20/25.
//

#include <stdint.h>

#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"


void HAL_Delay(uint32_t Delay) {
    vTaskDelay(pdMS_TO_TICKS(Delay));
}

void vApplicationTickHook(void) {
    HAL_IncTick();
}