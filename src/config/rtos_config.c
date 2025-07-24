//
// Created by Kok on 7/23/25.
//

#include "rtos_config.h"

#include <time.h>
#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"

#include "system_config.h"

void CONFIG_PreSleepProcessing(TickType_t xExpectedIdleTime) {
    // Sleep time of less than 1ms is not handled
    if ((pdTICKS_TO_MS(xExpectedIdleTime) / 1000) < 1) return;

    // 1Hz -> LSE clock selected
    if (HAL_RTCEx_SetWakeUpTimer_IT(systemConfig.pRTCHandle, pdTICKS_TO_MS(xExpectedIdleTime) / 1000, RTC_WAKEUPCLOCK_CK_SPRE_16BITS) != HAL_OK) return;

    HAL_SuspendTick();
}

void CONFIG_PostSleepProcessing(TickType_t xExpectedIdleTime) {
    HAL_RTCEx_DeactivateWakeUpTimer(systemConfig.pRTCHandle);
    HAL_ResumeTick();

    vTaskStepTick(xExpectedIdleTime);
}