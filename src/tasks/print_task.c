//
// Created by Kok on 7/20/25.
//

#include "print_task.h"

#include "system_config.h"
#include "message_buffers_config.h"

#include <stdio.h>
#include <string.h>

/**
 * @brief Prints message via USART1. This is intended to be used for printing when inside ISR.
 */
void TASK_Print(void *pvParams) {
    uint8_t message[MSG_BUFFER_SIZE_TASK_PRINT];

    while (1) {
        if (xMessageBufferReceive(systemMessageBuffers.pPrintTaskMessageBuffer, message, MSG_BUFFER_SIZE_TASK_PRINT, portMAX_DELAY)) {
            if (HAL_USART_Transmit(systemConfig.pUSARTHandle, message, strlen((char*)message), HAL_MAX_DELAY) != HAL_OK) {
                // TODO: Handle error...
                while (1);
            }
        }
    }
}

void printFromISR(uint8_t *msg, uint32_t len) {
    BaseType_t xHigherPriorityTestWoken = pdFALSE;
    xMessageBufferSendFromISR(systemMessageBuffers.pPrintTaskMessageBuffer, msg, len, &xHigherPriorityTestWoken);
    portYIELD_FROM_ISR(xHigherPriorityTestWoken);
}
