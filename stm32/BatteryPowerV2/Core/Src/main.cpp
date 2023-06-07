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

#include <stdlib.h>
#include <cstdio>
#include "command.hpp"
#include "diagnostics.hpp"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define SAMPLE_FREQ 100
#define SEND_FREQ 4
//#define SEND_FREQ 0.2

#define ENABLE_TLM

#define VOLTAGE_FILTER_A 0.7
#define CURRENT_FILTER_A 0.7
#define VDD_CURRENT_OFFSET 0.0
#define VCC_CURRENT_OFFSET 0.0
#define VPP_FIX (10.45 / 10.49)
#define VCC_FIX (5.03 / 4.69)
#define VDD_FIX (3.35 / 3.23)

#define VPP_V_MIN 7.0
#define VCC_V_MIN 4.9
#define VCC_V_MAX 5.1
#define VDD_V_MIN 3.2
#define VDD_V_MAX 3.4

#define CAN_SEND_TIMEOUT_TICK 20

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
 ADC_HandleTypeDef hadc;
DMA_HandleTypeDef hdma_adc;

CAN_HandleTypeDef hcan;

IWDG_HandleTypeDef hiwdg;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim14;

/* USER CODE BEGIN PV */

Diagnostics diag(MODULE_BATTERY);

CANChannel can;

CAN_TxHeaderTypeDef   CanTxHeader;
CAN_RxHeaderTypeDef   CanRxHeader;
uint8_t               CanTxData[8];
uint8_t               CanRxData[8];
uint32_t              CanTxMailbox;

uint32_t can_last_send_tick = 0;

uint16_t adc_values[10];

float vcc_A;
float vdd_A;
float vpp_V;
float vcc_V;
float vdd_V;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN_Init(void);
static void MX_DMA_Init(void);
static void MX_IWDG_Init(void);
static void MX_ADC_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM14_Init(void);
/* USER CODE BEGIN PFP */

extern "C" void initialise_monitor_handles(void);
void CAN_Send();
void CAN_Received();

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &htim2) {
    	float voltages[5];
    	for (int i = 0; i < 5; i++) {
    		voltages[i] = (float)adc_values[i] * 3.3 / 4095;
    	}

    	float vdd_A_ = (voltages[0] - 3.3 / 2.0) / 0.110 - VDD_CURRENT_OFFSET;
    	float vcc_A_ = (voltages[1] - 3.3 / 2.0) / 0.110 - VCC_CURRENT_OFFSET;
    	vpp_V = voltages[2] * 11.0 * VPP_FIX;
    	vdd_V = voltages[3] * 2.0 * VDD_FIX;
    	vcc_V = voltages[4] * 2.0 * VCC_FIX;

    	vcc_A = vcc_A * (1 - CURRENT_FILTER_A) + vcc_A_ * CURRENT_FILTER_A;
    	vdd_A = vdd_A * (1 - CURRENT_FILTER_A) + vdd_A_ * CURRENT_FILTER_A;

    	diag.setStatus(STATUS_0, vpp_V < VPP_V_MIN);
    	diag.setStatus(STATUS_1, vcc_V < VCC_V_MIN || VCC_V_MAX < vcc_V);
    	diag.setStatus(STATUS_2, vdd_V < VDD_V_MIN || VDD_V_MAX < vdd_V);
    }
    else if (htim == &htim14) {
    	diag.update(HAL_GetTick());

#ifdef DEBUG
		printf("Vpp: %d.%03d V\n", (int)vpp_V, abs((int)(vpp_V * 1000) % 1000));
		printf("Vcc: %d.%03d V, %d mA\n", (int)vcc_V, abs((int)(vcc_V * 1000) % 1000), (int)(vcc_A * 1000));
		printf("Vdd: %d.%03d V, %d mA\n", (int)vdd_V, abs((int)(vdd_V * 1000) % 1000), (int)(vdd_A * 1000));

		diag.printSummary();

#endif
		if (diag.getStatus(MODULE_BATTERY, STATUS_ALL) == STATUS_NG)
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		else
			HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

#ifdef ENABLE_TLM

		Command tlm('B', 0, 0, 6);

		tlm.entries[0].set('P', (float)vpp_V);
		tlm.entries[1].set('C', (float)vcc_V);
		tlm.entries[2].set('D', (float)vdd_V);
		tlm.entries[3].set('c', (float)vcc_A);
		tlm.entries[4].set('d', (float)vdd_A);
		volatile uint32_t d = diag.encode();
		tlm.entries[5].set('0' + MODULE_BATTERY_N, (uint32_t)d);

		can.tx.push(tlm);

		CAN_Send();
#endif
    }
}

void CAN_Received() {
	uint32_t raw;
	int32_t mid = can.rx.getDiag(raw);
	if (mid >= 0) diag.update(mid, raw, HAL_GetTick());
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
#ifdef DEBUG
  initialise_monitor_handles();
#endif
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
  MX_DMA_Init();
  MX_IWDG_Init();
  MX_ADC_Init();
  MX_TIM2_Init();
  MX_TIM14_Init();
  /* USER CODE BEGIN 2 */

  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  HAL_ADCEx_Calibration_Start(&hadc);
  HAL_ADC_Start_DMA(&hadc, (uint32_t*)adc_values, 10);

  HAL_Delay(1100);

  HAL_TIM_Base_Start_IT(&htim2);
  HAL_TIM_Base_Start_IT(&htim14);

  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);

#ifdef ENABLE_TLM

  Command tlm('R', 0, 0, 1);

  tlm.entries[0].set('B');

  can.tx.push(tlm);

  CAN_Send();
#endif

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  HAL_Delay(1);

#ifndef DEBUG
	  HAL_IWDG_Refresh(&hiwdg);
#endif
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI14|RCC_OSCILLATORTYPE_HSI48
                              |RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
  RCC_OscInitStruct.HSI14CalibrationValue = 16;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI48;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC_Init(void)
{

  /* USER CODE BEGIN ADC_Init 0 */

  /* USER CODE END ADC_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC_Init 1 */

  /* USER CODE END ADC_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc.Instance = ADC1;
  hadc.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.LowPowerAutoPowerOff = DISABLE;
  hadc.Init.ContinuousConvMode = ENABLE;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.DMAContinuousRequests = ENABLE;
  hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_5;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_7;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_8;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_9;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC_Init 2 */

  /* USER CODE END ADC_Init 2 */

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
  hcan.Init.Prescaler = 24;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_12TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_3TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = ENABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */


  CAN_FilterTypeDef filter0;
  uint32_t fId0   =  0x000 << 21;
  uint32_t fMask0 = (0x100 << 21) | 0x4;
  filter0.FilterIdHigh         = fId0 >> 16;
  filter0.FilterIdLow          = fId0;
  filter0.FilterMaskIdHigh     = fMask0 >> 16;
  filter0.FilterMaskIdLow      = fMask0;
  filter0.FilterScale          = CAN_FILTERSCALE_32BIT;
  filter0.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  filter0.FilterBank           = 0;
  filter0.FilterMode           = CAN_FILTERMODE_IDMASK;
  filter0.FilterActivation     = ENABLE;
  if (HAL_CAN_ConfigFilter(&hcan, &filter0) != HAL_OK)
  {
	Error_Handler();
  }

  CAN_FilterTypeDef filter1;
  uint32_t fId1   =  0x100 << 21;
  uint32_t fMask1 = (0x100 << 21) | 0x4;
  filter1.FilterIdHigh         = fId1 >> 16;
  filter1.FilterIdLow          = fId1;
  filter1.FilterMaskIdHigh     = fMask1 >> 16;
  filter1.FilterMaskIdLow      = fMask1;
  filter1.FilterScale          = CAN_FILTERSCALE_32BIT;
  filter1.FilterFIFOAssignment = CAN_FILTER_FIFO1;
  filter1.FilterBank           = 2;
  filter1.FilterMode           = CAN_FILTERMODE_IDMASK;
  filter1.FilterActivation     = ENABLE;
  if (HAL_CAN_ConfigFilter(&hcan, &filter1) != HAL_OK)
  {
	Error_Handler();
  }

  if (HAL_CAN_Start(&hcan) != HAL_OK)
  {
    /* Start Error */
    Error_Handler();
  }

  if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING | CAN_IT_RX_FIFO1_MSG_PENDING) != HAL_OK)
  {
    /* Notification Error */
    Error_Handler();
  }

  CanTxHeader.RTR   = CAN_RTR_DATA;
  CanTxHeader.IDE   = CAN_ID_STD;
  CanTxHeader.TransmitGlobalTime = DISABLE;

  /* USER CODE END CAN_Init 2 */

}

/**
  * @brief IWDG Initialization Function
  * @param None
  * @retval None
  */
static void MX_IWDG_Init(void)
{

  /* USER CODE BEGIN IWDG_Init 0 */

#ifdef DEBUG
  return;
#endif

  /* USER CODE END IWDG_Init 0 */

  /* USER CODE BEGIN IWDG_Init 1 */

  /* USER CODE END IWDG_Init 1 */
  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_16;
  hiwdg.Init.Window = 4095;
  hiwdg.Init.Reload = 4095;
  if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN IWDG_Init 2 */

  /* USER CODE END IWDG_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 48000 - 1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 1000 / SAMPLE_FREQ - 1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM14 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM14_Init(void)
{

  /* USER CODE BEGIN TIM14_Init 0 */

  /* USER CODE END TIM14_Init 0 */

  /* USER CODE BEGIN TIM14_Init 1 */

  /* USER CODE END TIM14_Init 1 */
  htim14.Instance = TIM14;
  htim14.Init.Prescaler = 48000 - 1;
  htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim14.Init.Period = 1000 / SEND_FREQ - 1;
  htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim14.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim14) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM14_Init 2 */

  /* USER CODE END TIM14_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

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
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

}


void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	/* Get RX message */
	if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &CanRxHeader, CanRxData) != HAL_OK) {
		/* Reception Error */
		Error_Handler();
	}

	if (can.receive(CanRxHeader.StdId, CanRxData, CanRxHeader.DLC)) {
		can.cancelSending();
		CAN_Received();
	}
}
void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	/* Get RX message */
	if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO1, &CanRxHeader, CanRxData) != HAL_OK) {
		/* Reception Error */
		Error_Handler();
	}

	if (can.receive(CanRxHeader.StdId, CanRxData, CanRxHeader.DLC)) {
		can.cancelSending();
		CAN_Received();
	}
}


/* USER CODE BEGIN 4 */

void CAN_Send() {
	while (true) {
		uint16_t std_id;
		uint8_t len;

		volatile uint32_t tick = HAL_GetTick();

		while (can.isReceiving()) {
			if (HAL_GetTick() - tick >= CAN_SEND_TIMEOUT_TICK) {
				can.cancelReceiving();
#ifdef DEBUG
				printf("BUSY\n");
#endif
			}
		}

		tick = HAL_GetTick();

		while (
//				HAL_GetTick() - tick <= 10 ||
				HAL_CAN_GetTxMailboxesFreeLevel(&hcan) != 3) {
			if (HAL_GetTick() - tick >= CAN_SEND_TIMEOUT_TICK) {
				HAL_CAN_AbortTxRequest(&hcan, CanTxMailbox);
				can.cancelSending();
#ifdef DEBUG
				printf("TIMEOUT\n");
#endif
				return;
			}
		}

		uint8_t remains = can.send(std_id, CanTxData, len);

		if (len == 0) return;

		CanTxHeader.StdId = std_id;
		CanTxHeader.DLC = len;


		if (HAL_CAN_AddTxMessage(&hcan, &CanTxHeader, CanTxData, &CanTxMailbox) != HAL_OK) {
			Error_Handler();
		}

//	#ifdef DEBUG
//		printf("Send %c(%x), %d: %c(%x) %x %x %x %x \n",
//				CanTxHeader.StdId, CanTxHeader.StdId, CanTxHeader.DLC,
//				CanTxData[0], CanTxData[0], CanTxData[1], CanTxData[2], CanTxData[3], CanTxData[4]);
//	#endif

		if (remains == 0) break;
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
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
