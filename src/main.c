
#include <stdio.h>
#include <stdlib.h>

#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"

#include "system_config.h"
#include "tasks_config.h"
#include "message_buffers_config.h"
#include "encoder_config.h"

#include "encoder_task.h"
#include "print_task.h"

USART_HandleTypeDef husart1 = {
    .Instance = USART1,
    .Init = {
        .Mode = USART_MODE_TX,
        .BaudRate = 9600,
        .Parity = USART_PARITY_NONE,
        .StopBits = USART_STOPBITS_1,
        .WordLength = USART_WORDLENGTH_8B,
    }
};

TIM_HandleTypeDef htim2 = {
    .Instance = TIM2,
    .Init = {
        .AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE,
        .ClockDivision = TIM_CLOCKDIVISION_DIV1,
        .CounterMode = TIM_COUNTERMODE_UP,
        .Prescaler = 0x00,
        .Period = ENCODER_TIM_ARR_VALUE - 1,
    }
};

RTC_HandleTypeDef hrtc = {
    .Instance = RTC,
    .Init = {}      // Clock functionality is not needed
};

System_Config_t systemConfig = {
    .pTIMHandle = &htim2,
    .pUSARTHandle = &husart1,
    .pRTCHandle = &hrtc
};

System_MessageBuffers_t systemMessageBuffers;

int __io_putchar(int ch) {
    HAL_USART_Transmit(systemConfig.pUSARTHandle, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

int main(void) {
    if (HAL_Init() != HAL_OK) {
        while (1);
    }

    if (HAL_USART_Init(systemConfig.pUSARTHandle) != HAL_OK) {
        while (1);
    }

    // Create message buffers
    systemMessageBuffers.pPrintTaskMessageBuffer = xMessageBufferCreate(MSG_BUFFER_SIZE_TASK_PRINT);

    // Initialize the encoder
    EncoderConfig();

    // Create encoder task
    if (xTaskCreate(encoderTask, TASK_NAME_ENCODER, 512, NULL, TASK_PRIORITY_ENCODER, &encoderTaskHandle) != pdPASS) {
        while (1);
    };

    // Create print task
    if (xTaskCreate(printTask, TASK_NAME_PRINT, 512, NULL, TASK_PRIORITY_PRINT, NULL) != pdPASS) {
        while (1);
    };

    vTaskStartScheduler();

    while (1);
}