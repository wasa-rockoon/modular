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
#define LORA_NRST_Pin GPIO_PIN_13
#define LORA_NRST_GPIO_Port GPIOC
#define LED_Pin GPIO_PIN_1
#define LED_GPIO_Port GPIOA
#define LORA_TRX_Pin GPIO_PIN_2
#define LORA_TRX_GPIO_Port GPIOA
#define SD_NSW_Pin GPIO_PIN_3
#define SD_NSW_GPIO_Port GPIOA
#define SD_SCK_Pin GPIO_PIN_13
#define SD_SCK_GPIO_Port GPIOB
#define SD_MISO_Pin GPIO_PIN_14
#define SD_MISO_GPIO_Port GPIOB
#define SD_MOSI_Pin GPIO_PIN_15
#define SD_MOSI_GPIO_Port GPIOB
#define LORA_NSLEEP_Pin GPIO_PIN_8
#define LORA_NSLEEP_GPIO_Port GPIOA
#define TWE_NRST_Pin GPIO_PIN_11
#define TWE_NRST_GPIO_Port GPIOA
#define LORA_RTX_Pin GPIO_PIN_15
#define LORA_RTX_GPIO_Port GPIOA
#define TWE_NSLEEP_Pin GPIO_PIN_3
#define TWE_NSLEEP_GPIO_Port GPIOB
#define TWE_NPGM_Pin GPIO_PIN_4
#define TWE_NPGM_GPIO_Port GPIOB
#define TWE_TRX_Pin GPIO_PIN_6
#define TWE_TRX_GPIO_Port GPIOB
#define TWE_RTX_Pin GPIO_PIN_7
#define TWE_RTX_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
