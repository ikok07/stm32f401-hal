//
// Created by Kok on 7/17/25.
//

#ifndef SYSTEM_CONFIG_H
#define SYSTEM_CONFIG_H

#include "stm32f4xx_hal.h"

#include "FreeRTOS.h"
#include "task.h"

#include "stream_buffer.h"
#include "message_buffer.h"

#define ENCODER_TIM_ARR_VALUE               65536

/* --------- IRQ Priorities --------- */

#define ENCODER_RESET_IRQ_PRIORITY           6
#define ENCODER_RESET_IRQ_SUBPRIORITY        1

#define ENCODER_TIM_IRQ_PRIORITY             6
#define ENCODER_TIM_IRQ_SUBPRIORITY          0

#define RTC_WKUP_IRQ_PRIORITY                5
#define RTC_WKUP_IRQ_SUBPRIORITY             0

typedef struct {
    TIM_HandleTypeDef *pTIMHandle;
    USART_HandleTypeDef *pUSARTHandle;
    RTC_HandleTypeDef *pRTCHandle;
} System_Config_t;

typedef struct {
    MessageBufferHandle_t pPrintTaskMessageBuffer;
} System_MessageBuffers_t;

typedef  struct {
    TaskHandle_t PrintTask;
    TaskHandle_t RTCConfigTask;
    TaskHandle_t EncoderTask;
} System_Tasks_t;

extern System_Config_t systemConfig;
extern System_Tasks_t systemTasks;
extern System_MessageBuffers_t systemMessageBuffers;

#endif //SYSTEM_CONFIG_H
