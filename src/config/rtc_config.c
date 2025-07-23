//
// Created by Kok on 7/23/25.
//

#include "rtc_config.h"

#include "stm32f4xx_hal.h"

#include "FreeRTOS.h"
#include "rtc_task.h"
#include "task.h"

#include "system_config.h"
#include "tasks_config.h"

RTC_HandleTypeDef hrtc = {
    .Instance = RTC,
    .Init = {
        .HourFormat = RTC_HOURFORMAT_24,
        .SynchPrediv = 128 - 1,
        .AsynchPrediv = 128 - 1,
        .OutPut = RTC_OUTPUT_DISABLE
    }
};

void APP_CreateRTCConfigTask() {
    systemConfig.pRTCHandle = &hrtc;
    if (xTaskCreate(TASK_RTCConfig, TASK_NAME_ENCODER_RTC_CONF, 512, NULL, TASK_PRIORITY_RTC_CONF, &systemTasks.pRTCConfigTask) != pdPASS) {
        while (1);
    }
}

void APP_ConfigureRTC() {
    systemConfig.pRTCHandle = &hrtc;

    // RTC clock is selected in the clock_config.c file
    if (HAL_RTC_Init(systemConfig.pRTCHandle) != HAL_OK) {
        while (1);
    };
}
