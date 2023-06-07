/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32l4xx_hal.h"

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_ERROR_Pin GPIO_PIN_0
#define LED_ERROR_GPIO_Port GPIOA
#define LED_STATUS_Pin GPIO_PIN_1
#define LED_STATUS_GPIO_Port GPIOA
#define TEMP_Pin GPIO_PIN_1
#define TEMP_GPIO_Port GPIOB
#define BNO_RESET_Pin GPIO_PIN_2
#define BNO_RESET_GPIO_Port GPIOB
#define GPS_1PPS_Pin GPIO_PIN_15
#define GPS_1PPS_GPIO_Port GPIOB
#define GPS_RESET_Pin GPIO_PIN_8
#define GPS_RESET_GPIO_Port GPIOA
#define GPS_TX_Pin GPIO_PIN_9
#define GPS_TX_GPIO_Port GPIOA
#define GPS_RX_Pin GPIO_PIN_10
#define GPS_RX_GPIO_Port GPIOA
#define TEMP_LOW_Pin GPIO_PIN_11
#define TEMP_LOW_GPIO_Port GPIOA
#define TEMP_HIGH_Pin GPIO_PIN_12
#define TEMP_HIGH_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
