//
// Created by Kok on 7/23/25.
//

#ifndef RTOS_CONFIG_H
#define RTOS_CONFIG_H

#include "FreeRTOS.h"
#include "task.h"

void CONFIG_PreSleepProcessing(TickType_t xExpectedIdleTime);
void CONFIG_PostSleepProcessing(TickType_t xExpectedIdleTime);

#endif //RTOS_CONFIG_H
