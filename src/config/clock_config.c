//
// Created by Kok on 7/23/25.
//

#include "clock_config.h"

#include "stm32f4xx_hal.h"

void APP_ConfigureClocks() {

    // All clocks (except low power) are configured for 16MHz

    RCC_ClkInitTypeDef clkConfig = {
        .ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_SYSCLK,
        .AHBCLKDivider = RCC_SYSCLK_DIV1,
        .APB1CLKDivider = RCC_HCLK_DIV1,
        .APB2CLKDivider = RCC_HCLK_DIV1,
        .SYSCLKSource = RCC_SYSCLKSOURCE_STATUS_HSI
    };

    RCC_OscInitTypeDef oscConfig = {
        .OscillatorType = RCC_OSCILLATORTYPE_LSE,
        .LSEState = RCC_LSE_ON          // Activate LSE
    };

    if (HAL_RCC_ClockConfig(&clkConfig, FLASH_LATENCY_0) != HAL_OK) {
        while (1);
    };

    if (HAL_RCC_OscConfig(&oscConfig) != HAL_OK) {
        while (1);
    };

    // Select LSE as RTC clock source
    RCC_PeriphCLKInitTypeDef periphConfig = {
        .PeriphClockSelection = RCC_PERIPHCLK_RTC,
        .RTCClockSelection = RCC_RTCCLKSOURCE_LSE
    };

    if (HAL_RCCEx_PeriphCLKConfig(&periphConfig) != HAL_OK) {
        while (1);
    }
}
