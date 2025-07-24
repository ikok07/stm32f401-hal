//
// Created by Kok on 7/23/25.
//

#include "rtc_task.h"
#include "rtc_config.h"

#include "FreeRTOS.h"
#include "task.h"

#include "system_config.h"

void TASK_RTCConfig() {
    APP_ConfigureRTC();
    vTaskDelete(systemTasks.RTCConfigTask);
}
