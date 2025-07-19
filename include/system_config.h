//
// Created by Kok on 7/17/25.
//

#ifndef SYSTEM_CONFIG_H
#define SYSTEM_CONFIG_H

#include "stm32f4xx_hal.h"

#define ENCODER_TIM_ARR_VALUE               65536

typedef struct {
    TIM_HandleTypeDef *pTIMHandle;
    USART_HandleTypeDef *pUSARTHandle;
    RTC_HandleTypeDef *pRTCHandle;
} System_Config_t;

extern System_Config_t systemConfig;

#endif //SYSTEM_CONFIG_H
