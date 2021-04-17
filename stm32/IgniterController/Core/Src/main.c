/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdbool.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN_Init(void);
/* USER CODE BEGIN PFP */
void CAN_Send(uint8_t *data, int length);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

CAN_TxHeaderTypeDef   CanTxHeader;
CAN_RxHeaderTypeDef   CanRxHeader;
uint8_t               CanRxData[8];
uint32_t              CanTxMailbox;

#define ARM_PERIOD          10000
#define SEND_STATE_INTERVAL 1000
#define ALIVE_INTERVAL      2000

#define LOOP_PERIOD         50

typedef enum {
	DEAD,
	DISARMED,
	EXPIRED,
	ARMED,
	FIRE,
} State;

State target_state     = DISARMED;
State pre_target_state = DISARMED;
State confirmed_state  = DEAD;

int send_state_timer = 0;
int alive_timer      = 0;


void send_state(void) {
	switch (target_state) {
	case DISARMED:
	case EXPIRED:
		CAN_Send((uint8_t *)"DISARM", 6);
		break;
	case ARMED:
		CAN_Send((uint8_t *)"ARM", 3);
		break;
	case FIRE:
		CAN_Send((uint8_t *)"FIRE", 4);
		break;
	default:
		break;
	}
	send_state_timer = 0;
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  int  arm_count = 0;

  /* USER CODE END 1 */


  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CAN_Init();
  /* USER CODE BEGIN 2 */

  HAL_GPIO_WritePin(Ind_GPIO_Port, Ind_Pin, GPIO_PIN_RESET);

  /* USER CODE END 2 */



  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  // Arm lever ON
	  if (confirmed_state == DISARMED &&
		  target_state != ARMED &&
		  target_state != EXPIRED &&
		  HAL_GPIO_ReadPin(Arm_GPIO_Port, Arm_Pin)) {
		  target_state = ARMED;
		  arm_count = 0;
	  }
	  // Arm lever OFF
	  if (!HAL_GPIO_ReadPin(Arm_GPIO_Port, Arm_Pin)) {
		  target_state = DISARMED;
	  }
	  // Arm period expired
	  if (target_state == ARMED &&
		  arm_count > ARM_PERIOD / LOOP_PERIOD) {
		  target_state = EXPIRED;
	  }
	  // Fire button pushed
	  if (confirmed_state == ARMED &&
		  target_state == ARMED &&
		  HAL_GPIO_ReadPin(Button_GPIO_Port, Button_Pin)) {
		  target_state = FIRE;
	  }

	  if (confirmed_state == DISARMED &&
		  target_state == FIRE) {
		  target_state = EXPIRED;
	  }


	  // Check heart beat
	  if (alive_timer > ALIVE_INTERVAL / LOOP_PERIOD) {
		  target_state    = DISARMED;
		  confirmed_state = DEAD;
	  }

	  // Send state
	  if (target_state != pre_target_state ||
		  send_state_timer > SEND_STATE_INTERVAL / LOOP_PERIOD) {
		  send_state();
	  }

	  pre_target_state = target_state;
	  arm_count++;
	  send_state_timer++;
	  alive_timer++;

	  HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

	  switch (confirmed_state) {
	  case DEAD:
		  HAL_GPIO_WritePin(Ind_GPIO_Port, Ind_Pin, GPIO_PIN_RESET);
		  break;
	  case DISARMED:
		  HAL_GPIO_WritePin(Ind_GPIO_Port, Ind_Pin,
				  alive_timer < 200 / LOOP_PERIOD ? GPIO_PIN_SET : GPIO_PIN_RESET);
		  break;
	  case ARMED:
		  HAL_GPIO_WritePin(Ind_GPIO_Port, Ind_Pin, GPIO_PIN_SET);
		  break;
	  case FIRE:
		  if (alive_timer % 2 == 0) HAL_GPIO_TogglePin(Ind_GPIO_Port, Ind_Pin);
		  break;
	  }

	  HAL_Delay(LOOP_PERIOD);


  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CAN Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */

  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
  hcan.Instance = CAN;
  hcan.Init.Prescaler = 25;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_13TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */

  // Configure Filter

  CAN_FilterTypeDef  fc;

  fc.FilterBank           = 0;
  fc.FilterMode           = CAN_FILTERMODE_IDMASK;
  fc.FilterScale          = CAN_FILTERSCALE_32BIT;
  fc.FilterIdHigh         = 0x0000;
  fc.FilterIdLow          = 0x0000;
  fc.FilterMaskIdHigh     = 0x0000;
  fc.FilterMaskIdLow      = 0x0000;
  fc.FilterFIFOAssignment = CAN_RX_FIFO0;
  fc.FilterActivation     = ENABLE;
  fc.SlaveStartFilterBank = 14;


  if (HAL_CAN_ConfigFilter(&hcan, &fc) != HAL_OK)
  {
    /* Filter configuration Error */
    Error_Handler();
  }

  if (HAL_CAN_Start(&hcan) != HAL_OK)
  {
    /* Start Error */
    Error_Handler();
  }


  if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
  {
    /* Notification Error */
    Error_Handler();
  }

  // Configure Transmission

  CanTxHeader.StdId = 0x12;
  CanTxHeader.RTR   = CAN_RTR_DATA;
  CanTxHeader.IDE   = CAN_ID_STD;
  CanTxHeader.TransmitGlobalTime = DISABLE;

  /* USER CODE END CAN_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_Pin|Ind_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_Pin Ind_Pin */
  GPIO_InitStruct.Pin = LED_Pin|Ind_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : Button_Pin */
  GPIO_InitStruct.Pin = Button_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Button_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Arm_Pin */
  GPIO_InitStruct.Pin = Arm_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Arm_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void CAN_Send(uint8_t *data, int length) {
	CanTxHeader.DLC = length;
	if (HAL_CAN_AddTxMessage(&hcan, &CanTxHeader, data, &CanTxMailbox) != HAL_OK) {
		/* Transmission request Error */
		Error_Handler();
	}
}

_Bool CAN_Received(uint32_t id, uint8_t *data, uint32_t length) {
	if (CanRxHeader.StdId != id)         return 0;
	if (CanRxHeader.IDE   != CAN_ID_STD) return 0;
	if (CanRxHeader.DLC   != length)     return 0;
	for (int i = 0; i < length; i++) {
		if (CanRxData[i] != data[i]) return 0;
	}
	return 1;
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  /* Get RX message */
  if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &CanRxHeader, CanRxData) != HAL_OK)
  {
    /* Reception Error */
    Error_Handler();
  }

  alive_timer = 0;

  if (CAN_Received((uint32_t)0x13, (uint8_t*)"DISARM", 6)) {
	  confirmed_state = DISARMED;
  }
  else if (CAN_Received((uint32_t)0x13, (uint8_t*)"ARM", 3)) {
	  confirmed_state = ARMED;
  }
  else if (CAN_Received((uint32_t)0x13, (uint8_t*)"FIRE", 4)) {
  	  confirmed_state = FIRE;
  }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
