//
// Created by Kok on 7/20/25.
//

#ifndef PRINT_TASK_H
#define PRINT_TASK_H

#include <stdint.h>

void TASK_Print(void *pvParams);
void printFromISR(uint8_t *msg, uint32_t len);

#endif //PRINT_TASK_H
