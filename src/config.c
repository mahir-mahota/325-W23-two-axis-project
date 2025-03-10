/**
  ******************************************************************************
  * @file    config.h
  * @date    02/11/2025 17:40:52
  * @brief   This file contains config function definitions for the lab
  ******************************************************************************
  */

#include "config.h"
#include "L6470.h"

int x_direction = 1;
int y_direction = 1;
int x_states[2] = {0, 0};
int y_states[2] = {0, 0};

/**
 * @brief  Limit switch GPIO initialization
 */
void LS_Init (void) {
  // Configure GPIO pins
  GPIO_InitTypeDef GPIO_Y_LS_1;
  GPIO_Y_LS_1.Pin = GPIO_PIN_8|GPIO_PIN_9;
  GPIO_Y_LS_1.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_Y_LS_1.Pull = GPIO_NOPULL;
  GPIO_Y_LS_1.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(Y_AXIS_PORT, &GPIO_Y_LS_1);

  GPIO_InitTypeDef GPIO_X_LS_1;
  GPIO_X_LS_1.Pin = GPIO_PIN_6|GPIO_PIN_7;
  GPIO_X_LS_1.Mode = GPIO_MODE_IT_RISING_FALLING;
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
  uint8_t direction = L6470_CheckStatusRegisterFlag(L6470_Id, DIR_ID);
  L6470_Run(L6470_Id, direction ^ 1, MAX_MOTOR_SPEED);
}

/**
 * @brief  Check motor states at program start for validity
 */
void init_motor_states(void) {
  x_states[0] = HAL_GPIO_ReadPin(X_AXIS_PORT, X_AXIS_PIN_0);
  x_states[1] = HAL_GPIO_ReadPin(X_AXIS_PORT, X_AXIS_PIN_1);
  y_states[0] = HAL_GPIO_ReadPin(Y_AXIS_PORT, Y_AXIS_PIN_0);
  y_states[1] = HAL_GPIO_ReadPin(Y_AXIS_PORT, Y_AXIS_PIN_1);

  if (!x_states[1]) {
    L6470_Run(X_AXIS_MOTOR_ID, L6470_DIR_FWD_ID, MAX_MOTOR_SPEED);
  } else if (!x_states[0]) {
    L6470_Run(X_AXIS_MOTOR_ID, L6470_DIR_REV_ID, MAX_MOTOR_SPEED);
    x_direction = 0;
  }

  if (!y_states[1]) {
    L6470_Run(Y_AXIS_MOTOR_ID, L6470_DIR_FWD_ID, MAX_MOTOR_SPEED);
  } else if (!y_states[0]) {
    L6470_Run(Y_AXIS_MOTOR_ID, L6470_DIR_REV_ID, MAX_MOTOR_SPEED);
    y_direction = 0;
  }
}

/**
 * @brief  Process interrupt for change in state of either motor
 */
void process_motor_state(uint8_t L6470_Id, int switch_dir) {
  int pin_state = -1;
  if (L6470_Id == X_AXIS_MOTOR_ID) {
    pin_state = switch_dir ? HAL_GPIO_ReadPin(X_AXIS_PORT, X_AXIS_PIN_1) : HAL_GPIO_ReadPin(X_AXIS_PORT, X_AXIS_PIN_0);
    x_states[switch_dir] = pin_state;
    if (pin_state && switch_dir == x_direction && !x_states[switch_dir ^ 0x1]) {
      L6470_Reverse(L6470_Id);
      x_direction ^= 1;
    } else if (pin_state && x_states[switch_dir ^ 0x1]) {
      L6470_HardStop(L6470_Id);
    } else if (!pin_state && x_states[switch_dir ^ 0x1]) {
      L6470_Run(X_AXIS_MOTOR_ID, switch_dir, MAX_MOTOR_SPEED);
      x_direction = switch_dir;
    }
  } else if (L6470_Id == Y_AXIS_MOTOR_ID) {
    pin_state = switch_dir ? HAL_GPIO_ReadPin(Y_AXIS_PORT, Y_AXIS_PIN_1) : HAL_GPIO_ReadPin(Y_AXIS_PORT, Y_AXIS_PIN_0);
    y_states[switch_dir] = pin_state;
    if (pin_state && switch_dir == y_direction && !y_states[switch_dir ^ 0x1]) {
      L6470_HardStop(L6470_Id);
      L6470_Reverse(L6470_Id);
      y_direction ^= 1;
    } else if (pin_state && y_states[switch_dir ^ 0x1]) {
      L6470_HardStop(L6470_Id);
    } else if (!pin_state && y_states[switch_dir ^ 0x1]) {
      L6470_Run(Y_AXIS_MOTOR_ID, switch_dir, MAX_MOTOR_SPEED);
      y_direction = switch_dir;
    }
  }

  for (volatile int i = 0; i < 10000; i++) {
    __NOP();
  }
}
