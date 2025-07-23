//
// Created by Kok on 7/23/25.
//

#include "usart_config.h"

#include "stm32f4xx_hal.h"

#include "FreeRTOS.h"
#include "task.h"

#include "system_config.h"
#include "tasks_config.h"
#include "message_buffers_config.h"

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

int __io_putchar(int ch) {
    HAL_USART_Transmit(systemConfig.pUSARTHandle, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

void APP_ConfigureUSART1() {
    systemConfig.pUSARTHandle = &husart1;

    if (HAL_USART_Init(systemConfig.pUSARTHandle) != HAL_OK) {
        while (1);
    }

    // Create message buffers
    systemMessageBuffers.pPrintTaskMessageBuffer = xMessageBufferCreate(MSG_BUFFER_SIZE_TASK_PRINT);

    if (xTaskCreate(TASK_Print, TASK_NAME_PRINT, 512, NULL, TASK_PRIORITY_PRINT, &systemTasks.pPrintTask) != pdPASS) {
        while (1);
    };
}
