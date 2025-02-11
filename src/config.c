/**
  ******************************************************************************
  * @file    config.h
  * @date    02/11/2025 17:40:52
  * @brief   This file contains config function definitions for the lab
  ******************************************************************************
  */

#include "config.h"

/**
 * @brief  Limit switch GPIO initialization
 */
void LS_Init (void) {   
    // Configure GPIO pins
    GPIO_InitTypeDef GPIO_Y_LS_1;
    GPIO_Y_LS_1.Pin = GPIO_PIN_8;
    GPIO_Y_LS_1.Mode = GPIO_MODE_INPUT;
    GPIO_Y_LS_1.Mode = GPIO_MODE_IT_RISING;
    GPIO_Y_LS_1.Pull = GPIO_NOPULL;
    GPIO_Y_LS_1.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(Y_AXIS_PORT, &GPIO_Y_LS_1);

    GPIO_InitTypeDef GPIO_Y_LS_2;
    GPIO_Y_LS_2.Pin = GPIO_PIN_9;
    GPIO_Y_LS_2.Mode = GPIO_MODE_INPUT;
    GPIO_Y_LS_2.Mode = GPIO_MODE_IT_RISING;
    GPIO_Y_LS_2.Pull = GPIO_NOPULL;
    GPIO_Y_LS_2.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(Y_AXIS_PORT, &GPIO_Y_LS_2);

    GPIO_InitTypeDef GPIO_X_LS_1;
    GPIO_X_LS_1.Pin = GPIO_PIN_6;
    GPIO_X_LS_1.Mode = GPIO_MODE_INPUT;
    GPIO_X_LS_1.Mode = GPIO_MODE_IT_RISING;
    GPIO_X_LS_1.Pull = GPIO_NOPULL;
    GPIO_X_LS_1.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(X_AXIS_PORT, &GPIO_X_LS_1);

    GPIO_InitTypeDef GPIO_X_LS_2;
    GPIO_X_LS_2.Pin = GPIO_PIN_7;
    GPIO_X_LS_2.Mode = GPIO_MODE_INPUT;
    GPIO_X_LS_2.Mode = GPIO_MODE_IT_RISING;
    GPIO_X_LS_2.Pull = GPIO_NOPULL;
    GPIO_X_LS_2.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(X_AXIS_PORT, &GPIO_X_LS_2);

    // Enable interrupts
    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}
  