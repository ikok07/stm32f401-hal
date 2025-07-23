//
// Created by Kok on 7/23/25.
//

#include "rtos_config.h"

#include <time.h>
#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"

#include "system_config.h"

RTC_DateTypeDef rtcDate;
RTC_TimeTypeDef rtcTime;
time_t sleepStartTimestamp = 0;

static time_t convert_to_timestamp(RTC_DateTypeDef *date, RTC_TimeTypeDef *time) {
    struct tm timeinfo = {0};

    timeinfo.tm_year = date->Year + 100;
    timeinfo.tm_mon = date->Month - 1;
    timeinfo.tm_mday = date->Date;
    timeinfo.tm_hour = time->Hours;
    timeinfo.tm_min = time->Minutes;
    timeinfo.tm_sec = time->Seconds;

    return mktime(&timeinfo);
}

void CONFIG_PreSleepProcessing(TickType_t xExpectedIdleTime) {
    // Sleep time of less than 2ms is not handled
    // if ((xExpectedIdleTime / configTICK_RATE_HZ) < 2) return;

    // 1Hz -> LSE clock selected
    // TODO: FIX INCORRECT COUNTER VALUE
    if (HAL_RTCEx_SetWakeUpTimer_IT(systemConfig.pRTCHandle, xExpectedIdleTime / configTICK_RATE_HZ, RTC_WAKEUPCLOCK_RTCCLK_DIV2) != HAL_OK) return;

    if (HAL_RTC_GetTime(systemConfig.pRTCHandle, &rtcTime, RTC_FORMAT_BIN) != HAL_OK) {
        HAL_RTCEx_DeactivateWakeUpTimer(systemConfig.pRTCHandle);
        return;
    }
    if (HAL_RTC_GetDate(systemConfig.pRTCHandle, &rtcDate, RTC_FORMAT_BIN) != HAL_OK) {
        HAL_RTCEx_DeactivateWakeUpTimer(systemConfig.pRTCHandle);
        return;
    }

    sleepStartTimestamp = convert_to_timestamp(&rtcDate, &rtcTime);

    HAL_SuspendTick();
}

void CONFIG_PostSleepProcessing() {
    HAL_RTCEx_DeactivateWakeUpTimer(systemConfig.pRTCHandle);
    HAL_ResumeTick();

    if (HAL_RTC_GetTime(systemConfig.pRTCHandle, &rtcTime, RTC_FORMAT_BIN) != HAL_OK) return;
    if (HAL_RTC_GetDate(systemConfig.pRTCHandle, &rtcDate, RTC_FORMAT_BIN) != HAL_OK) return;

    time_t currentTimestamp = convert_to_timestamp(&rtcDate, &rtcTime);
    vTaskStepTick(pdMS_TO_TICKS((currentTimestamp - sleepStartTimestamp) * 1000));
}