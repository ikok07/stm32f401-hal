//
// Created by Kok on 7/20/25.
//

#include <stdio.h>
#include <stdint.h>

#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"

#include "system_config.h"
#include "encoder_task.h"
#include "print_task.h"

int32_t prevCounter = -1;
uint32_t encoderValue = 0;

TaskHandle_t encoderTaskHandle;

void encoderTask(void *pvParams) {
    printf("Saved encoder value: %ld\n", encoderValue);

    while (1) {
        if (xTaskNotifyWait(0, 0, NULL, portMAX_DELAY)) {
            uint16_t counter = __HAL_TIM_GET_COUNTER(systemConfig.pTIMHandle);
            int16_t diff = counter - prevCounter;

            if (diff > (ENCODER_TIM_ARR_VALUE - 1) / 2) diff -= ENCODER_TIM_ARR_VALUE;
            else if (diff < -(ENCODER_TIM_ARR_VALUE / 2)) diff += ENCODER_TIM_ARR_VALUE;

            if (diff > 0) encoderValue++;
            else if (diff < 0) encoderValue--;
            HAL_RTCEx_BKUPWrite(systemConfig.pRTCHandle, RTC_BKP_DR0, encoderValue);
            printf("Encoder value: %ld\n", encoderValue);
            prevCounter = counter;
        }
    }
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM2) {
        BaseType_t xHigherPriorityTestWoken = pdFALSE;
        vTaskNotifyGiveFromISR(encoderTaskHandle, &xHigherPriorityTestWoken);
        portYIELD_FROM_ISR(xHigherPriorityTestWoken);
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    encoderValue = 0;

    // Send message
    uint8_t msg[] = "Encoder value reset to 0\n";
    printFromISR(msg, sizeof(msg));
}