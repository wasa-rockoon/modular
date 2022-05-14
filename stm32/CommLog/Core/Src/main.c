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
#include <command.hpp>
#include <main.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_rx;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_CAN_Init(void);
/* USER CODE BEGIN PFP */

void TWE_Transmit(char*);
void CAN_Send(uint8_t *data, int length);


void encodeMessage(const Message *m, uint8_t* buf);
bool decodeMessage(Message *m, const uint8_t* buf);

uint8_t encodeHexMessage(const Message *m, uint8_t* buf);
bool decodeHexMessage(Message *m, const uint8_t* buf);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

extern void initialise_monitor_handles(void);

#define DBG false


CAN_TxHeaderTypeDef   CanTxHeader;
CAN_RxHeaderTypeDef   CanRxHeader;
uint8_t               CanRxData[8];
uint32_t              CanTxMailbox;


char txbuf[256];



#define RXBUFSIZE 256

typedef struct {
	UART_HandleTypeDef *handle;
	uint8_t  rxbuf[RXBUFSIZE * 2];
	uint32_t rx_start;
	uint32_t rx_read;
	bool     overran;
} UART;

void UART_Init(UART *uart, UART_HandleTypeDef *handle) {
	uart->handle    = handle;
	uart->rx_start  = handle->hdmarx->Instance->CNDTR == 0
					? 0
					: RXBUFSIZE - handle->hdmarx->Instance->CNDTR;
	uart->rx_read   = uart->rx_start;
	uart->overran   = false;
	HAL_UART_Receive_DMA(handle, uart->rxbuf, RXBUFSIZE);
}

uint32_t ringbuf_index(UART *uart) {
	volatile uint32_t cndtr = uart->handle->hdmarx->Instance->CNDTR;
	return RXBUFSIZE - cndtr;
}

uint32_t pullout_ringbuf(UART *uart) {
	volatile uint32_t *cndtr = &(uart->handle->hdmarx->Instance->CNDTR);
	uint32_t index = ringbuf_index(uart);
	if (index < uart->rx_read) {

		for (int i = 0; i < index; i++) {
			uart->rxbuf[RXBUFSIZE + i] = uart->rxbuf[i];
		}
		return RXBUFSIZE + index;
	}
	else {
		(*cndtr)++;
		if (*cndtr >= RXBUFSIZE) *cndtr = 0;
		return index;
	}
}

uint8_t* UART_Read(UART *uart) {
	uint32_t index = ringbuf_index(uart);
	uint32_t start = uart->rx_read;
	if (index == start) return NULL;

	uint32_t end = pullout_ringbuf(uart);

	uart->rxbuf[end] = 0;
	uart->rx_read    = index;
	uart->rx_start   = index;

	if (start == end) return NULL;

	return uart->rxbuf + start;
}

uint8_t* UART_Read_Until(UART *uart, char term) {
	uint32_t index = ringbuf_index(uart);
	uint32_t start = uart->rx_read;

	if (index == uart->rx_start ||
		index + RXBUFSIZE == uart->rx_start) return NULL;

	uint32_t end = pullout_ringbuf(uart);

	int i = uart->rx_start;
	while (i < end) {
		if (uart->rxbuf[i] == term) {

			uart->rxbuf[i] = 0;
			uart->rx_read  = uart->rx_read >= RXBUFSIZE ? index : i + 1;
			uart->rx_start = uart->rx_read;
			return uart->rxbuf + start;
		}
		i++;
	}
	uart->rx_start = i;
	if (uart->rx_read != uart->rx_start) {
//		printf("###\n");
	}
	return NULL;
}

uint8_t* UART_Read_Line(UART *uart) {
	return UART_Read_Until(uart, '\n');
}

void UART_Send(UART *uart, uint8_t* str, unsigned int length) {
	HAL_UART_Transmit(uart->handle,(uint8_t *)str, length, 0xFFFF);
}

UART twe_uart;

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

	if (DBG) initialise_monitor_handles();


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
  /* USER CODE BEGIN 2 */

//  HAL_UART_Receive_IT(&huart1, rxbuf, RXSIZE);

  UART_Init(&twe_uart, &huart1);


  // Reset TWELITE

  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  HAL_GPIO_WritePin(TWE_NRST_GPIO_Port, TWE_NRST_Pin, GPIO_PIN_RESET);
  HAL_Delay(100);
  HAL_GPIO_WritePin(TWE_NRST_GPIO_Port, TWE_NRST_Pin, GPIO_PIN_SET);

  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);

  // Setup TWELITE


//  for (int i = 0; i < 3; i++) {
//	  TWE_Transmit("+");
//	  TWE_Receive_and_Print();
//	  HAL_Delay(300);
//  }
//  TWE_Transmit("mD\nS");
//  TWE_Receive_and_Print();

  Message message;

  if (DBG) printf("Start\n");


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  uint8_t* rx = UART_Read_Line(&twe_uart);
	  if (rx != NULL) {

		  int start;
		  for (start = 0; start < 64; start++) {
			  if (rx[start] != '\0' && rx[start] != '\r' && rx[start] != '\n') break;
		  }
		  int i;
		  for (i = start; i < 64; i++) {
			  if (rx[i] == '\0' || rx[i] == '\r' || rx[i] == '\n') break;
		  }

		  if (i - start == 16) {
			  bool success = decodeHexMessage(&message, rx + start);

			  if (DBG) printf("%u %c %u %c %u %u\n", success, message.id, message.seq, message.type, message.index, message.payload);

			  if (success) {
				  uint8_t tx[8];
				  encodeMessage(&message, tx);

				  CAN_Send((uint8_t*)(tx), 8);
				  HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
			  }
		  }


//		  if (DBG) printf("%s %d\n", rx + start, i);
//		  CAN_Send((uint8_t*)(rx + start), i);

	  }

//	  CAN_Send((uint8_t*)"AAA", 3);
//	  HAL_Delay(1000);
	  //printf("%ld %s %ld\n", CanRxHeader.IDE, CanRxData, CanRxHeader.DLC);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
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

  CanTxHeader.StdId = 0x13;
  CanTxHeader.RTR   = CAN_RTR_DATA;
  CanTxHeader.IDE   = CAN_ID_STD;
  CanTxHeader.TransmitGlobalTime = DISABLE;

  /* USER CODE END CAN_Init 2 */

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
  huart1.Init.BaudRate = 115200;
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

  __HAL_UART_DISABLE_IT(&huart1, UART_IT_ERR);

  /* USER CODE END USART1_Init 2 */

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

  /*Configure GPIO pins : LED_Pin TWE_NRST_Pin */
  GPIO_InitStruct.Pin = LED_Pin|TWE_NRST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

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

  if (CanRxHeader.DLC < 8) return;

  Message message;
  bool success = decodeMessage(&message, CanRxData);
  if (!success) return;

  uint8_t tx[18];
  uint8_t count = encodeHexMessage(&message, tx);


  UART_Send(&twe_uart, tx, count);
  HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

  if (DBG) printf("%ld %s %ld\n", CanRxHeader.StdId, CanRxData, CanRxHeader.DLC);
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
