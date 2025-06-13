/**
  ******************************************************************************
  * @file    config.h
  * @date    02/11/2025 17:39:48
  * @brief   This file contains functiopn declarations and macros for the lab
  ******************************************************************************
  */
#pragma once

#include "stm32f4xx_hal.h"

#define Y_AXIS_PORT         GPIOB
#define Y_AXIS_PIN_0        GPIO_PIN_8
#define Y_AXIS_PIN_1        GPIO_PIN_9
#define X_AXIS_PORT         GPIOC
#define X_AXIS_PIN_0        GPIO_PIN_6
#define X_AXIS_PIN_1        GPIO_PIN_7

#define Y_AXIS_MOTOR_ID     0
#define X_AXIS_MOTOR_ID     1

#define ADC1_PORT           GPIOA
#define ADC2_PORT           GPIOB
#define ADC_PIN             GPIO_PIN_0

#define MAX_X_MOTOR_SPEED   10000
#define MAX_Y_MOTOR_SPEED   30000
#define MAX_ADC             4095

void LS_Init (void);
void ADC_GPIO_Init(void);
void L6470_Reverse(uint8_t L6470_Id);
void init_motor_states(void);
void process_motor_state(uint8_t L6470_Id, int switch_dir);
void set_motor_speed(uint8_t L6470_Id, int adc_value);
