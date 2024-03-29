/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <cstdio>
#include <time.h>
#include "command.hpp"
#include "diagnostics.hpp"
#include "bmp280.hpp"
#include "TinyGPS++.h"
#include "uart.hpp"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

//#define TEST

#define CAN_SEND_TIMEOUT_TICK 10

#define SAMPLE_FREQ 100
#define TLM_FREQ 10

#define GPS_LOST_TICK 10000

#define PRESSURE_FILTER_A 0.5
#define SPEED_FILTER_A 0.99

#define ALTITUDE_DIFF 1000

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
FDCAN_HandleTypeDef hfdcan1;

IWDG_HandleTypeDef hiwdg;

SPI_HandleTypeDef hspi2;

TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_rx;


/* USER CODE BEGIN PV */

Diagnostics diag(MODULE_NAV);

BMP280 bmp280(hspi2, CS_PRES_GPIO_Port, CS_PRES_Pin);
bool bmp280_ok;

TinyGPSPlus gps;
UART gps_uart(huart2);

CANChannel can;

FDCAN_TxHeaderTypeDef CanTxHeader;
FDCAN_RxHeaderTypeDef CanRxHeader;
uint8_t               CanTxData[8];
uint8_t               CanRxData[8];
uint32_t              CanTxMailbox;

float pressure_raw;
float p_altitude_raw;
float temperature_raw;
float p_v_speed_raw;
float pressure;
float p_altitude;
float temperature;
float p_v_speed;

float qnh_pa = 101325;

#ifdef TEST
float gps_altitude;
#endif

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_FDCAN1_Init(void);
static void MX_IWDG_Init(void);
static void MX_SPI2_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM4_Init(void);
/* USER CODE BEGIN PFP */
extern "C" void initialise_monitor_handles(void);
void CAN_Send();
void CAN_Received();
void Measure();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &htim3) {
    	// Sample

    	float p_altitude_p = p_altitude;

#ifdef TEST
    	pressure_raw    -= 10;
    	p_altitude_raw  += 1;
    	temperature_raw -= 0.001;
    	gps_altitude    += 1;
#else
    	pressure_raw    = bmp280.readPressure();
    	p_altitude_raw  = bmp280.readAltitude(qnh_pa / 100.0);
    	temperature_raw = bmp280.readTemperature();
#endif

    	pressure    = pressure    * (1 - PRESSURE_FILTER_A) + pressure_raw    * PRESSURE_FILTER_A;
    	p_altitude  = p_altitude  * (1 - PRESSURE_FILTER_A) + p_altitude_raw  * PRESSURE_FILTER_A;
    	temperature = temperature * (1 - PRESSURE_FILTER_A) + temperature_raw * PRESSURE_FILTER_A;

    	p_v_speed_raw  = (p_altitude - p_altitude_p) * SAMPLE_FREQ;

    	p_v_speed   = p_v_speed   * (1 - SPEED_FILTER_A) + p_v_speed_raw * SPEED_FILTER_A;

    }
    else if (htim == &htim4) {

//    	if (!gps.location.isValid()) {
    	Measure();
//    	}


  #ifndef DEBUG
    	HAL_IWDG_Refresh(&hiwdg);
  #endif
    }
}


void Measure() {

	bool location_ok = gps.location.age() < GPS_LOST_TICK;
	bool altitude_ok = gps.altitude.age() < GPS_LOST_TICK;
	bool altitude_same = abs(gps.altitude.meters() - p_altitude) < ALTITUDE_DIFF;

	diag.setStatus(STATUS_0, !location_ok);
	diag.setStatus(STATUS_1, !altitude_ok);
	diag.setStatus(STATUS_2, !bmp280_ok);
	diag.setStatus(STATUS_3, !altitude_same);
	diag.update(HAL_GetTick());

	Command pos('P', 0, 0, 2);
	pos.entries[0].set('P', (float)p_altitude);
	pos.entries[1].set('V', (float)p_v_speed);

	if (location_ok) {
		pos.entries[2].set('O', (float)gps.location.lng());
		pos.entries[3].set('A', (float)gps.location.lat());

		pos.size += 2;
	}


#ifdef TEST
	pos.entries[pos.size].set('H', gps_altitude);

	pos.size++;
#else

	pos.entries[pos.size].set('H', (float)gps.altitude.meters());

	pos.size++;
#endif


	can.tx.push(pos);

	Command env('E', 0, 0, 3);
	env.entries[0].set('P', (float)pressure);
	env.entries[1].set('I', (float)temperature);
	env.entries[2].set('0' + MODULE_NAV_N, (uint32_t)diag.encode());

	if (gps.date.age() < GPS_LOST_TICK) {
		env.entries[env.size].set('D', (uint32_t)gps.date.value());
		env.size++;
	}
	if (gps.time.age() < GPS_LOST_TICK) {
		env.entries[env.size].set('T', (uint32_t)gps.time.value());
		env.size++;
	}
	if (gps.satellites.age() < GPS_LOST_TICK) {
		env.entries[env.size].set('S', (int32_t)gps.satellites.value());
		env.size++;
	}

	can.tx.push(env);

	CAN_Send();

//
#ifdef DEBUG
//	printf("P %d\n", (int)(pressure));
//	printf("H %d\n", (int)(p_altitude));
//	printf("T %d\n", (int)(temperature));
//	printf("GPS: %d\n", gps.location.isValid());
//	printf("Lat: %d\n", (int)(gps.location.lng() * 1000));
//	printf("Lng: %d\n", (int)(gps.location.lat() * 1000));
//	printf("Alt: %d\n", (int)(gps.altitude.meters()));
//	diag.printSummary();
#endif

	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
}



void CAN_Received() {
	uint32_t raw;
	int32_t mid = can.rx.getDiag(raw);
	if (mid >= 0) diag.update(mid, raw, HAL_GetTick());

	if (can.rx.id == 's') {
		qnh_pa = can.rx.get('Q', 0, qnh_pa);

		Command setting('s', 0, 0, 1);
		setting.entries[0].set('Q', qnh_pa);
		can.tx.push(setting);
		CAN_Send();
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
  MX_FDCAN1_Init();
  MX_IWDG_Init();
  MX_SPI2_Init();
  MX_USART2_UART_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
#ifdef DEBUG
  printf("Start\n");
#endif


  HAL_Delay(100);

  bmp280_ok = bmp280.begin();
  HAL_Delay(100);
  bmp280_ok = bmp280.begin();

#ifdef DEBUG
  printf("BMP %d", bmp280_ok);
#endif

  bmp280.setSampling(BMP280::MODE_NORMAL,     /* Operating Mode. */
		  	  	     BMP280::SAMPLING_X2,     /* Temp. oversampling */
					 BMP280::SAMPLING_X16,    /* Pressure oversampling */
					 BMP280::FILTER_X16,      /* Filtering. */
					 BMP280::STANDBY_MS_500); /* Standby time. */

#ifdef TEST
  gps_altitude = 10000;
  p_altitude_raw = 10000;
  p_altitude = 10000;
#else
  pressure    = bmp280.readPressure();
  p_altitude  = bmp280.readAltitude(qnh_pa / 100.0);
  temperature = bmp280.readTemperature();
#endif

  HAL_TIM_Base_Start_IT(&htim3);
  HAL_TIM_Base_Start_IT(&htim4);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  while (!gps_uart.rxIsEmpty()) {
		  uint8_t c = gps_uart.read();
		  gps.encode(c);
//		  printf("%c", c);
	  }

	  if (gps.location.isValid() && gps.location.isUpdated()) {
//		  Measure();
	  }
//
//	  if (len > 0) {
//		  lwgps_process(&gps, gps_data, len);
//	  }

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

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 75;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief FDCAN1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_FDCAN1_Init(void)
{

  /* USER CODE BEGIN FDCAN1_Init 0 */

  /* USER CODE END FDCAN1_Init 0 */

  /* USER CODE BEGIN FDCAN1_Init 1 */

  /* USER CODE END FDCAN1_Init 1 */
  hfdcan1.Instance = FDCAN1;
  hfdcan1.Init.ClockDivider = FDCAN_CLOCK_DIV1;
  hfdcan1.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
  hfdcan1.Init.Mode = FDCAN_MODE_NORMAL;
  hfdcan1.Init.AutoRetransmission = ENABLE;
  hfdcan1.Init.TransmitPause = DISABLE;
  hfdcan1.Init.ProtocolException = DISABLE;
  hfdcan1.Init.NominalPrescaler = 24;
  hfdcan1.Init.NominalSyncJumpWidth = 1;
  hfdcan1.Init.NominalTimeSeg1 = 19;
  hfdcan1.Init.NominalTimeSeg2 = 5;
  hfdcan1.Init.DataPrescaler = 1;
  hfdcan1.Init.DataSyncJumpWidth = 1;
  hfdcan1.Init.DataTimeSeg1 = 1;
  hfdcan1.Init.DataTimeSeg2 = 1;
  hfdcan1.Init.StdFiltersNbr = 2;
  hfdcan1.Init.ExtFiltersNbr = 0;
  hfdcan1.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
  if (HAL_FDCAN_Init(&hfdcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN FDCAN1_Init 2 */


  FDCAN_FilterTypeDef filter0;
  filter0.IdType = FDCAN_STANDARD_ID;
  filter0.FilterIndex = 0;
  filter0.FilterType = FDCAN_FILTER_MASK;
  filter0.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
  filter0.FilterID1 = 0x000;
  filter0.FilterID2 = 0x100;
  if (HAL_FDCAN_ConfigFilter(&hfdcan1, &filter0) != HAL_OK)
  {
	Error_Handler();
  }

  FDCAN_FilterTypeDef filter1;
  filter1.IdType = FDCAN_STANDARD_ID;
  filter1.FilterIndex = 1;
  filter1.FilterType = FDCAN_FILTER_MASK;
  filter1.FilterConfig = FDCAN_FILTER_TO_RXFIFO1;
  filter1.FilterID1 = 0x100;
  filter1.FilterID2 = 0x100;
  if (HAL_FDCAN_ConfigFilter(&hfdcan1, &filter1) != HAL_OK)
  {
	Error_Handler();
  }

  if (HAL_FDCAN_Start(&hfdcan1) != HAL_OK)
  {
	  Error_Handler();
  }

  if (HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE | FDCAN_IT_RX_FIFO1_NEW_MESSAGE, 0) != HAL_OK)
  {
    Error_Handler();
  }

  CanTxHeader.IdType = FDCAN_STANDARD_ID;
  CanTxHeader.TxFrameType = FDCAN_DATA_FRAME;
  CanTxHeader.DataLength = FDCAN_DLC_BYTES_8;
  CanTxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
  CanTxHeader.BitRateSwitch = FDCAN_BRS_OFF;
  CanTxHeader.FDFormat = FDCAN_CLASSIC_CAN;
  CanTxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
  CanTxHeader.MessageMarker = 0;

  /* USER CODE END FDCAN1_Init 2 */

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
  hspi2.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi2.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
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
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 15000-1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 10000 / SAMPLE_FREQ - 1;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 15000-1;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 10000 / TLM_FREQ - 1;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

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
  huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  HAL_UART_Receive_DMA(&huart2, gps_uart.rx_buf(), RXBUFSIZE);

  /* USER CODE END USART2_Init 2 */

}


/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMAMUX1_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
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
  HAL_GPIO_WritePin(GPIOA, LED_Pin|CS_ACCL_Pin|CS_MAG_Pin|CS_GYRO_Pin
                          |CS_PRES_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : DRDYM_Pin */
  GPIO_InitStruct.Pin = DRDYM_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(DRDYM_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : CS_ACCL_Pin CS_MAG_Pin CS_GYRO_Pin CS_PRES_Pin */
  GPIO_InitStruct.Pin = CS_ACCL_Pin|CS_MAG_Pin|CS_GYRO_Pin|CS_PRES_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}


void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
	if (hfdcan->Instance == hfdcan1.Instance) {
		  if ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET) {
			 if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &CanRxHeader, CanRxData) != HAL_OK){
				 Error_Handler();
			 }

//			 printf("0%c\n", CanRxData[0]);
//			 if (can.receive(CanRxHeader.Identifier, CanRxData, CanRxHeader.DataLength)) {
//				 can.cancelSending();
//				 CAN_Received();
//			 }
		}
	}
}

void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo1ITs)
{
	if (hfdcan->Instance == hfdcan1.Instance) {
		  if ((RxFifo1ITs & FDCAN_IT_RX_FIFO1_NEW_MESSAGE) != RESET) {
			 if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO1, &CanRxHeader, CanRxData) != HAL_OK){
				 Error_Handler();
			 }

//			 printf("1%c\n", CanRxData[0]);
//			 if (can.receive(CanRxHeader.Identifier, CanRxData, CanRxHeader.DataLength)) {
//				 can.cancelSending();
//				 CAN_Received();
//			 }
		}
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
				printf("B\n");
		#endif
				return;
			}
		}

		while (HAL_FDCAN_GetTxFifoFreeLevel(&hfdcan1) != 3) {
			if (HAL_GetTick() - tick >= CAN_SEND_TIMEOUT_TICK) {
				HAL_FDCAN_AbortTxRequest(&hfdcan1, 0);
				can.cancelSending();
#ifdef DEBUG
				printf("T\n");
#endif
				return;
			}
		}

		uint8_t remains = can.send(std_id, CanTxData, len);

		if (len == 0) return;

		CanTxHeader.Identifier = std_id;
		CanTxHeader.DataLength = len << 16;

		if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &CanTxHeader, CanTxData) != HAL_OK) {
			Error_Handler();
		}

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
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
//
