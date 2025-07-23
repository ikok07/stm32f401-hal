//
// Created by Kok on 7/20/25.
//

#ifndef ENCODER_TASK_H
#define ENCODER_TASK_H

#include "FreeRTOS.h"
#include "task.h"

extern int32_t prevCounter;
extern uint32_t encoderValue;

void TASK_Encoder(void *pvParams);

#endif //ENCODER_TASK_H
