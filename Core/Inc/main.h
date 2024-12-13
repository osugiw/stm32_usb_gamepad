/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wbxx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdbool.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

// Button state for controlling system state
typedef struct{
	bool leftJS_isPressed;
	bool rightJS_isPressed;
	bool a_isPressed;
	bool b_isPressed;
}buttonState_t;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
extern uint8_t joystick_X, joystick_Y, joystick_RX, joystick_RY;
extern buttonState_t bt_states;
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define joystick_sw_Pin GPIO_PIN_13
#define joystick_sw_GPIO_Port GPIOC
#define joystick_x_Pin GPIO_PIN_0
#define joystick_x_GPIO_Port GPIOC
#define joystick_y_Pin GPIO_PIN_1
#define joystick_y_GPIO_Port GPIOC
#define joystick_ry_Pin GPIO_PIN_0
#define joystick_ry_GPIO_Port GPIOA
#define joystick_rx_Pin GPIO_PIN_1
#define joystick_rx_GPIO_Port GPIOA
#define joystick_rsw_Pin GPIO_PIN_8
#define joystick_rsw_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
