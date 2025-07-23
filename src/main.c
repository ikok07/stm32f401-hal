
#include <stdio.h>
#include <stdlib.h>

#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"

#include "system_config.h"
#include "clock_config.h"
#include "rtc_config.h"
#include "usart_config.h"
#include "tasks_config.h"
#include "encoder_config.h"

#include "encoder_task.h"
#include "print_task.h"

System_Config_t systemConfig;
System_Tasks_t systemTasks;
System_MessageBuffers_t systemMessageBuffers;

int main(void) {
    if (HAL_Init() != HAL_OK) {
        while (1);
    }

    // Configure the clocks
    APP_ConfigureClocks();

    // Create RTC Configuration task
    APP_CreateRTCConfigTask();

    // Initialize the USART peripheral for printing
    APP_ConfigureUSART1();

    // Initialize the encoder
    APP_ConfigureEncoder();

    vTaskStartScheduler();

    while (1);
}