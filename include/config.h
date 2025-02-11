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
#define X_AXIS_PORT         GPIOC
#define Y_AXIS_MOTOR_ID     0
#define X_AXIS_MOTOR_ID     1

void LS_Init (void);
