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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SAMPLE_FREQ 1000
#define TLM_FREQ 10
#define LED_ERROR_Pin GPIO_PIN_0
#define LED_ERROR_GPIO_Port GPIOA
#define LED_STATUS_Pin GPIO_PIN_1
#define LED_STATUS_GPIO_Port GPIOA
#define TEMP_Pin GPIO_PIN_2
#define TEMP_GPIO_Port GPIOA
#define VDD_V_Pin GPIO_PIN_3
#define VDD_V_GPIO_Port GPIOA
#define VDD_I_Pin GPIO_PIN_4
#define VDD_I_GPIO_Port GPIOA
#define VCC_V_Pin GPIO_PIN_5
#define VCC_V_GPIO_Port GPIOA
#define VCC_I_Pin GPIO_PIN_6
#define VCC_I_GPIO_Port GPIOA
#define BAT2_V_Pin GPIO_PIN_7
#define BAT2_V_GPIO_Port GPIOA
#define BAT1_V_Pin GPIO_PIN_0
#define BAT1_V_GPIO_Port GPIOB
#define VPP_V_Pin GPIO_PIN_1
#define VPP_V_GPIO_Port GPIOB
#define HEATER_Pin GPIO_PIN_9
#define HEATER_GPIO_Port GPIOA
#define SUPPLY_CON_Pin GPIO_PIN_10
#define SUPPLY_CON_GPIO_Port GPIOA
#define SUPPLY_3V3_Pin GPIO_PIN_11
#define SUPPLY_3V3_GPIO_Port GPIOA
#define SUPPLY_5V_Pin GPIO_PIN_12
#define SUPPLY_5V_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
