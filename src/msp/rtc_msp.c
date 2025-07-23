//
// Created by Kok on 7/23/25.
//

#include "stm32f4xx_hal.h"
#include "system_config.h"

void HAL_RTC_MspInit(RTC_HandleTypeDef *hrtc) {
    __HAL_RCC_RTC_ENABLE();

    HAL_NVIC_SetPriority(RTC_WKUP_IRQn, RTC_WKUP_IRQ_PRIORITY, RTC_WKUP_IRQ_SUBPRIORITY);
    HAL_NVIC_EnableIRQ(RTC_WKUP_IRQn);
}
