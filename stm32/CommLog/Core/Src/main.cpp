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
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <cstdio>
#include "command.hpp"
#include "uart.hpp"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SEND_TIMEOUT_TICK 40000
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
 CAN_HandleTypeDef hcan;

IWDG_HandleTypeDef hiwdg;

SPI_HandleTypeDef hspi2;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;
DMA_HandleTypeDef hdma_usart2_rx;
DMA_HandleTypeDef hdma_usart2_tx;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_CAN_Init(void);
static void MX_IWDG_Init(void);
static void MX_SPI2_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

extern "C" void initialise_monitor_handles(void);
void CAN_Send();

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

CANChannel can;
HexChannel sd;

UART twelite(huart1);
UART lora(huart2);

CAN_TxHeaderTypeDef   CanTxHeader;
CAN_RxHeaderTypeDef   CanRxHeader;
uint8_t               CanTxData[8];
uint8_t               CanRxData[8];
uint32_t              CanTxMailbox;

FATFS fs;  // file system
FIL fil; // File
FILINFO fno;
FRESULT fresult;  // result
UINT br, bw;  // File read/write count

bool file_opened = false;


void TWE_Init() {

	HAL_GPIO_WritePin(TWE_NRST_GPIO_Port, TWE_NRST_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(TWE_NRST_GPIO_Port, TWE_NRST_Pin, GPIO_PIN_SET);
}

void LoRa_Init() {

}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	while (HAL_CAN_GetRxFifoFillLevel(hcan, CAN_RX_FIFO0) > 0) {
		/* Get RX message */
		if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &CanRxHeader, CanRxData) != HAL_OK) {
		    /* Reception Error */
		    Error_Handler();
		}

		if (!file_opened) return;

		if (can.receive(CanRxHeader.StdId, CanRxData, CanRxHeader.DLC)) {

			sd.tx = can.rx;

			uint8_t buf[14];
			uint8_t len;

			while (true) {
				int remains = sd.send(buf, len);

				if (len == 0) continue;

				f_puts((char*)buf, &fil);

				if (remains == 0) break;
			}

			HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		}

#ifdef DEBUG
		printf("%c(%x), %d: %c(%x) %x %x %x %x \n",
				CanRxHeader.StdId, CanRxHeader.StdId, CanRxHeader.DLC,
				CanRxData[0], CanRxData[0], CanRxData[1], CanRxData[2], CanRxData[3], CanRxData[4]);
#endif
	}
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
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_CAN_Init();
  MX_IWDG_Init();
  MX_SPI2_Init();
  MX_FATFS_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */


#ifdef DEBUG
  printf("Start\n");
#endif

  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  TWE_Init();

  LoRa_Init();


  fresult = f_mount(&fs, "/", 1);

  // Check free space
  FATFS *pfs;
  DWORD fre_clust;
  f_getfree("", &fre_clust, &pfs);

  uint32_t total = (uint32_t)((pfs->n_fatent - 2) * pfs->csize * 0.5);
  uint32_t free_space = (uint32_t)(fre_clust * pfs->csize * 0.5);



  fresult = f_open(&fil, "lists.txt", FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
  uint32_t file_id = f_size(&fil);
  for (unsigned n = 0; n < file_id; n++) f_putc('1', &fil);
  fresult = f_close(&fil);

  char file_name[16];
  sprintf(file_name, "log%05u.txt", (unsigned)file_id);

  	/* Open file to write/ create a file if it doesn't exist */
  fresult = f_open(&fil, file_name, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);

  if (fresult == FR_OK) file_opened = true;

#ifdef DEBUG
  printf("File opened: %s, total: %d, free: %d, %d\n",
		  file_name, total, free_space, fresult);
#endif


  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  HAL_Delay(1000);

	  if (file_opened) f_sync(&fil);

	  // HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//
//	  uint8_t* rx;
//	  unsigned len = UART_Read(&rx);
//
//	  Command *command = readHex(&twe_channel, rx, len);
//
//#ifdef DEBUG
//	  if (len > 0) {
//		  //printf("uart %.*s (%d)\n", len, rx, len);
//	  }
//	  if (command) {
//		  printCommand(command);
//	  }
//#endif
//	  if (command) {
//		  while (true) {
//			  uint8_t tx[8];
//			  int remains = writeCAN(&can_channel, command, tx);
//			  CAN_Send(tx, 8);
//
//			  //HAL_Delay(10);
//
//			  if (remains == 0) break;
//		  }
//		  HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//	  }

//	  CAN_Send((uint8_t*)"AAA", 3);
//	  HAL_Delay(1000);
	  //printf("%ld %s %ld\n", CanRxHeader.IDE, CanRxData, CanRxHeader.DLC);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
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
  hcan.Init.Prescaler = 8;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_4TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_1TQ;
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

  CAN_FilterTypeDef filter;
  filter.FilterIdHigh         = 0;
  filter.FilterIdLow          = 0;
  filter.FilterMaskIdHigh     = 0;
  filter.FilterMaskIdLow      = 0;
  filter.FilterScale          = CAN_FILTERSCALE_32BIT;
  filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  filter.FilterBank           = 0;
  filter.FilterMode           = CAN_FILTERMODE_IDMASK;
  filter.SlaveStartFilterBank = 14;
  filter.FilterActivation     = ENABLE;
  if (HAL_CAN_ConfigFilter(&hcan, &filter) != HAL_OK)
  {
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
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 7;
  hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi2.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 38400;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
		Error_Handler();
	}
  /* USER CODE BEGIN USART1_Init 2 */

	__HAL_UART_DISABLE_IT(&huart1, UART_IT_PE);
	__HAL_UART_DISABLE_IT(&huart1, UART_IT_ERR);
	HAL_UART_Receive_DMA(&huart1, twelite.rx_buf(), RXBUFSIZE);

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

	__HAL_UART_DISABLE_IT(&huart2, UART_IT_PE);
	__HAL_UART_DISABLE_IT(&huart2, UART_IT_ERR);
	HAL_UART_Receive_DMA(&huart2, lora.rx_buf(), RXBUFSIZE);


  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel2_3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel2_3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);
  /* DMA1_Channel4_5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel4_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel4_5_IRQn);

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
  HAL_GPIO_WritePin(GPIOA, LED_Pin|TWE_NRST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, TWE_NSLEEP_Pin|TWE_NPGM_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : LED_Pin TWE_NRST_Pin */
  GPIO_InitStruct.Pin = LED_Pin|TWE_NRST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : SD_NSW_Pin */
  GPIO_InitStruct.Pin = SD_NSW_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(SD_NSW_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : TWE_NSLEEP_Pin TWE_NPGM_Pin */
  GPIO_InitStruct.Pin = TWE_NSLEEP_Pin|TWE_NPGM_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void CAN_Send() {
	uint8_t std_id, len;

	while (can.isReceiving() || can.isSending());

	while (true) {
		int remains = can.send(std_id, CanTxData, len);

		if (len == 0) continue;
		CanTxHeader.StdId = std_id;
		CanTxHeader.DLC = len;

		int tick = 0;
		while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan) != 3) {
			if (tick > SEND_TIMEOUT_TICK) {
				can.cancelSending();
				return;
			}
			tick++;
		}
		if (HAL_CAN_AddTxMessage(&hcan, &CanTxHeader, CanTxData, &CanTxMailbox) != HAL_OK) {
			Error_Handler();
		}

		if (remains == 0) break;
	}
}


//
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle){
////	printf("I");
//	if(UartHandle->Instance == USART1){
//		printf("%s", rxbuf);
////		__HAL_UART_SEND_REQ(&huart1, UART_RXDATA_FLUSH_REQUEST);
////		HAL_UART_Receive_IT(&huart1, rxbuf, RXSIZE);
//		HAL_UART_Receive_DMA(&huart1, rxbuf, RXSIZE);
//	}
//}
//
//void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle) {
////	HAL_UART_Abort(&huart1);
//	printf("Error\n");
////	HAL_UART_Receive_IT(&huart1, rxbuf, RXSIZE);
////	HAL_UART_Receive_DMA(&huart1, rxbuf, RXSIZE);
//}
//
//int TWE_ECHO() {
//	HAL_UART_Receive(&huart1,(uint8_t *)rxbuf, sizeof(rxbuf), 0xF);
//	if (rxbuf[0] != 0) {
//		printf("%s", rxbuf);
//		TWE_Transmit(rxbuf);
//		rxbuf[0] = 0;
//		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//		return 1;
//	}
//	else return 0;
//}
//
//int TWE_Receive_and_Print() {
//	HAL_UART_Receive(&huart1,(uint8_t *)rxbuf, sizeof(rxbuf), 0xF);
//	if (rxbuf[0] != 0) {
//		printf("%s\n", rxbuf);
//		rxbuf[0] = 0;
//		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//		return 1;
//	}
//	else return 0;
//}
//
//void TWE_Transmit(char* str) {
//	HAL_UART_Transmit(&huart1,(uint8_t *)str, sizeof(str), 0xFFFF);
//}

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
