//
// Created by Kok on 7/20/25.
//

#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"

#include "system_config.h"
#include "encoder_task.h"

void EncoderConfig() {
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
}
