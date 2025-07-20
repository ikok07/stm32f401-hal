
#include <stdio.h>
#include <stdlib.h>

#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"

#include "system_config.h"
#include "tasks_config.h"
#include "encoder_task.h"

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

    TIM_Encoder_InitTypeDef TIM_EncoderConfig = {
        .EncoderMode = TIM_ENCODERMODE_TI1,

        .IC1Polarity = TIM_ENCODERINPUTPOLARITY_RISING,
        .IC1Selection = TIM_ICSELECTION_INDIRECTTI,
        .IC1Prescaler = TIM_ICPSC_DIV1,
        .IC1Filter = 0x0F,

        .IC2Polarity =  TIM_ENCODERINPUTPOLARITY_RISING,
        .IC2Selection = TIM_ICSELECTION_INDIRECTTI,
        .IC2Prescaler = TIM_ICPSC_DIV1,
        .IC2Filter = 0x0F
    };

    __HAL_RCC_PWR_CLK_ENABLE();

    HAL_PWR_EnableBkUpAccess();
    if (HAL_PWREx_EnableBkUpReg() != HAL_OK) {
        while (1);
    };

    if (HAL_TIM_Encoder_Init(systemConfig.pTIMHandle, &TIM_EncoderConfig) != HAL_OK) {
        while (1);
    }

    if (HAL_TIM_Encoder_Start_IT(systemConfig.pTIMHandle, TIM_CHANNEL_ALL) != HAL_OK) {
        while (1);
    };

    encoderValue = HAL_RTCEx_BKUPRead(systemConfig.pRTCHandle, RTC_BKP_DR0);

    // Create encoder task
    if (xTaskCreate(encoderTask, TASK_NAME_ENCODER, 100, NULL, TASK_PRIORITY_ENCODER, &encoderTaskHandle) != pdPASS) {
        while (1);
    };

    vTaskStartScheduler();

    while (1);
}