/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_ERROR_Pin GPIO_PIN_0
#define LED_ERROR_GPIO_Port GPIOA
#define LED_A_Pin GPIO_PIN_1
#define LED_A_GPIO_Port GPIOA
#define LED_B_Pin GPIO_PIN_2
#define LED_B_GPIO_Port GPIOA
#define LED_C_Pin GPIO_PIN_3
#define LED_C_GPIO_Port GPIOA
#define LED_D_Pin GPIO_PIN_4
#define LED_D_GPIO_Port GPIOA
#define X_DATA_Pin GPIO_PIN_6
#define X_DATA_GPIO_Port GPIOA
#define X_SCK_Pin GPIO_PIN_7
#define X_SCK_GPIO_Port GPIOA
#define PRESSURE_Pin GPIO_PIN_0
#define PRESSURE_GPIO_Port GPIOB
#define POWER_FB_Pin GPIO_PIN_1
#define POWER_FB_GPIO_Port GPIOB
#define Y_DATA_Pin GPIO_PIN_10
#define Y_DATA_GPIO_Port GPIOB
#define Y_SCK_Pin GPIO_PIN_11
#define Y_SCK_GPIO_Port GPIOB
#define POWER_ON_Pin GPIO_PIN_12
#define POWER_ON_GPIO_Port GPIOB
#define VALVE_D_Pin GPIO_PIN_13
#define VALVE_D_GPIO_Port GPIOB
#define VALVE_C_Pin GPIO_PIN_14
#define VALVE_C_GPIO_Port GPIOB
#define VALVE_B_Pin GPIO_PIN_15
#define VALVE_B_GPIO_Port GPIOB
#define VALVE_A_Pin GPIO_PIN_8
#define VALVE_A_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
