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
// #include <command.h>
#include <cstdio>
#include "bmx055.hpp"
#include "algebra.hpp"

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

SPI_HandleTypeDef hspi2;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN_Init(void);
static void MX_SPI2_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

void TWE_Transmit(char*);
void CAN_Send(uint8_t *data, int length);

//
//void encodeMessage(const Message *m, uint8_t* buf);
//bool decodeMessage(Message *m, const uint8_t* buf);
//
//uint8_t encodeHexMessage(const Message *m, uint8_t* buf);
//bool decodeHexMessage(Message *m, const uint8_t* buf);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

extern "C" void initialise_monitor_handles(void);


CAN_TxHeaderTypeDef   CanTxHeader;
CAN_RxHeaderTypeDef   CanRxHeader;
uint8_t               CanRxData[8];
uint32_t              CanTxMailbox;



#define RXBUFSIZE 256
#define TXBUFSIZE 32

uint8_t rxbuf[RXBUFSIZE];
uint8_t txbuf[TXBUFSIZE];

unsigned rx_read = 0;

void UART_Init() {
	rx_read = huart2.hdmarx->Instance->CNDTR == 0
			? 0
			: RXBUFSIZE - huart2.hdmarx->Instance->CNDTR;
	HAL_UART_Receive_DMA(&huart2, rxbuf, RXBUFSIZE);
}

unsigned UART_Read(uint8_t** buf) {
	// printf("read %d %d \n", huart1.hdmarx->Instance->CNDTR, rx_read);
	unsigned index = RXBUFSIZE - huart2.hdmarx->Instance->CNDTR;
	if (index == RXBUFSIZE) index = 0;

	if (index == rx_read) {
		return 0;
	}
	else if (index < rx_read) {
		*buf = rxbuf + rx_read;
		unsigned len = RXBUFSIZE - rx_read;
		rx_read = 0;
		return len;
	}
	else {
		*buf = rxbuf + rx_read;
		unsigned len = index - rx_read;
		rx_read = index;
		return len;
	}
}

// HexChannel twe_channel;
// CANChannel can_channel;

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
  MX_SPI2_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

//  HAL_UART_Receive_IT(&huart1, rxbuf, RXSIZE);

  // UART_Init();


  BMX055 bmx055(hspi2);

#ifdef DEBUG
  printf("Start\n");
#endif

  bmx055.begin();

//  bmx055.Gyro.sellect();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  HAL_Delay(200);

	  Vec3 accel = bmx055.Accl.read();
	  Vec3 gyro = bmx055.Gyro.read();
	  Vec3 mag = bmx055.Mag.read();

#ifdef DEBUG
	  char buf[64];
	  accel.show(buf);
	  printf("A %s\n", buf);
	  gyro.show(buf);
	  printf("G %s\n", buf);
	  mag.show(buf);
	  printf("M %s\n", buf);

#endif

	  HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
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

  CanTxHeader.StdId = 0x15;
  CanTxHeader.RTR   = CAN_RTR_DATA;
  CanTxHeader.IDE   = CAN_ID_STD;
  CanTxHeader.TransmitGlobalTime = DISABLE;

  /* USER CODE END CAN_Init 2 */

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
  hspi2.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi2.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
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
  huart2.Init.BaudRate = 9600;
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

  /* USER CODE END USART2_Init 2 */

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

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, CS_ACCEL_Pin|CS_GYRO_Pin|CS_MAG_Pin|CS_PRESS_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : LED_Pin CS_ACCEL_Pin CS_GYRO_Pin CS_MAG_Pin
                           CS_PRESS_Pin */
  GPIO_InitStruct.Pin = LED_Pin|CS_ACCEL_Pin|CS_GYRO_Pin|CS_MAG_Pin
                          |CS_PRESS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */


void CAN_Send(uint8_t *data, int length) {
	int i = 0;

	CanTxHeader.DLC = length;
	if (HAL_CAN_AddTxMessage(&hcan, &CanTxHeader, data, &CanTxMailbox) != HAL_OK) {
		/* Transmission request Error */
		Error_Handler();
	}

//	uint32_t fl = HAL_CAN_GetTxMailboxesFreeLevel(&hcan);
//
	while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan) != 3) {
		i++;
		if (i > 10000000) break;
 	}

	//HAL_Delay(1);

#ifdef DEBUG
	for (int n = 0; n < 8; n++) {
		printf("%X ", data[n]);
	}
	printf("\n");
#endif
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  /* Get RX message */
  if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &CanRxHeader, CanRxData) != HAL_OK)
  {
    /* Reception Error */
    Error_Handler();
  }

  if (CanRxHeader.DLC < 8) return;
//
//  Message message;
//  bool success = decodeMessage(&message, CanRxData);
//  if (!success) return;
//
//  uint8_t tx[18];
//  uint8_t count = encodeHexMessage(&message, tx);
//
//
//  UART_Send(&twe_uart, tx, count);
  HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

#ifdef DEBUG
  printf("%ld %s %ld\n", CanRxHeader.StdId, CanRxData, CanRxHeader.DLC);
#endif
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
