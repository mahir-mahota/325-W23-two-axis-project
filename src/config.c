/**
  ******************************************************************************
  * @file    config.h
  * @date    02/11/2025 17:40:52
  * @brief   This file contains config function definitions for the lab
  ******************************************************************************
  */

#include "config.h"
#include "L6470.h"

/**
 * @brief  Limit switch GPIO initialization
 */
void LS_Init (void) {   
  // Configure GPIO pins
  GPIO_InitTypeDef GPIO_Y_LS_1;
  GPIO_Y_LS_1.Pin = GPIO_PIN_8|GPIO_PIN_9;
  GPIO_Y_LS_1.Mode = GPIO_MODE_IT_RISING;
  GPIO_Y_LS_1.Pull = GPIO_NOPULL;
  GPIO_Y_LS_1.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(Y_AXIS_PORT, &GPIO_Y_LS_1);

  GPIO_InitTypeDef GPIO_X_LS_1;
  GPIO_X_LS_1.Pin = GPIO_PIN_6|GPIO_PIN_7;
  GPIO_X_LS_1.Mode = GPIO_MODE_IT_RISING;
  GPIO_X_LS_1.Pull = GPIO_NOPULL;
  GPIO_X_LS_1.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(X_AXIS_PORT, &GPIO_X_LS_1);

  // Enable interrupts
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}

/**
 * @brief  ADC1/8 GPIO initialization
 */
void ADC_GPIO_Init(void) {
  GPIO_InitTypeDef ADC_GPIO;
  ADC_GPIO.Pin = ADC_PIN;
  ADC_GPIO.Mode = GPIO_MODE_ANALOG;
  ADC_GPIO.Pull = GPIO_NOPULL;
  ADC_GPIO.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(ADC1_PORT, &ADC_GPIO);
  HAL_GPIO_Init(ADC2_PORT, &ADC_GPIO);
}

/**
 * @brief  Reverese motor direction
 */
void L6470_Reverse(uint8_t L6470_Id) {
  // uint32_t speed = L6470_GetParam(L6470_Id, L6470_MAX_SPEED_ID);
  uint8_t x_direction = L6470_CheckStatusRegisterFlag(L6470_Id, DIR_ID);
  x_direction ^= 1;
  L6470_Run(L6470_Id, x_direction, CURR_SPEED);
}
