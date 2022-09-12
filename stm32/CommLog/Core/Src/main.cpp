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
#ifdef DEBUG
#define MAX_ENTRIES 8
#endif
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <cstdio>
#include <string.h>
#include "command.hpp"
#include "uart.hpp"
#include "es920lr.hpp"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */


#define LAUNCHER

#ifndef LAUNCHER
#define GS
#endif

#define LORA_SETUP

#define SD_SYNC_TICK 100

const char PANID[] = "0110";

#ifdef LAUNCHER
const char OWN_ID[] = "0000";
const char DEST_ADDR[] = "FFFF";
#define SEND_IFREQ 13
#endif
#ifdef GS
const char OWN_ID[] = "0001";
//const char OWN_ID[] = "0002";
const char DEST_ADDR[] = "0000";
#define SEND_IFREQ 17
#endif

//#define LORA_BAUD 115200
#define LORA_BAUD 38400


#define CAN_SEND_TIMEOUT_TICK 10

#define LORA_TIMEOUT_TICK 30000

#define UPLINK_WAIT_TICK 5000
#define SETTING_CONFIRM_TICK 1000

#define BLINK_TICK 500

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

TIM_HandleTypeDef htim14;

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
static void MX_TIM14_Init(void);
/* USER CODE BEGIN PFP */

extern "C" void initialise_monitor_handles(void);
void Blink();
void CAN_Send();

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

CANChannel can;
HexChannel sd;

UART twelite(huart1);
ES920LR lora(huart2);

CAN_TxHeaderTypeDef   CanTxHeader;
CAN_RxHeaderTypeDef   CanRxHeader;
uint8_t               CanTxData[8];
uint8_t               CanRxData[8];
uint32_t              CanTxMailbox;

uint32_t can_last_send_tick = 0;
uint32_t sd_last_sync_tick = 0;
uint32_t lora_last_send_tick = 0;

FATFS fs;  // file system
FIL fil; // File
FILINFO fno;
FRESULT fresult;  // result
UINT br, bw;  // File read/write count

bool file_opened = false;

uint32_t blink_tick = 0;

#ifdef LAUNCHER

Command tlm_nav('n', 'L', 0, 0);
Command tlm_mode('m', 'L', 0, 0);
Command tlm_launcher('l', 'L', 0, 0);
Command tlm_settings('s', 'L', 0, 0);

enum class TlmState {
	Init,
	SendingNav,
	SendingMode,
	SendingLauncher,
	WaitingUplink,
	ConfirmingSettings,
	SendingSettings,
};

TlmState tlm_state = TlmState::Init;

uint32_t tlm_state_tick = 0;

#endif

#ifdef GS

Command command_mode;
Command command_settings;

bool send_settings = false;

#endif

#ifdef LAUNCHER
void ChangeState(TlmState new_state) {
	tlm_state = new_state;
	tlm_state_tick = HAL_GetTick();
#ifdef DEBUG
	switch (new_state) {
	case TlmState::Init:
		printf("Init State\n");
		break;
	case TlmState::SendingNav:
		printf("Sending Nav Tlm\n");
		break;
	case TlmState::SendingMode:
		printf("Sending Mode Tlm\n");
		break;
	case TlmState::SendingLauncher:
		printf("Sending Launcher Tlm\n");
		break;
	case TlmState::WaitingUplink:
		printf("Waiting Uplink\n");
		break;
	case TlmState::ConfirmingSettings:
		printf("Confirming Settings\n");
		break;
	case TlmState::SendingSettings:
		printf("Sending Settings Tlm\n");
		break;
	}
#endif
}
#endif

void LoRa_Setup() {
	lora.begin(true);

	lora.config('b', "3", 1); // Bandwidth
	lora.config('c', "12", 2); // Spreading factor
	lora.config('d', "3", 1); // channel
	lora.config('e', PANID, 4); // PAN ID
	lora.config('f', OWN_ID, 4); // Own ID
	lora.config('g', DEST_ADDR, 4); // Destination ID
	lora.config('n', "2", 1); // Transfer mode
	lora.config('o', "1", 1); // Receive ID
	lora.config('p', "1", 1); // RSSI
	lora.config('u', "13", 2); // Power
	lora.config('A', "2", 1); // Payload format
#ifdef LAUNCHER
	lora.config('a', "1", 1); // Node
	lora.config('l', "2", 1); // Ack
#endif
#ifdef GS
	lora.config('a', "2", 1); // Node
	lora.config('l', "1", 1); // Ack
#endif
	lora.config('w', "", 0); // save
}

bool SD_Init() {
	fresult = f_mount(&fs, "/", 1);

	// Check free space
	FATFS *pfs;
	DWORD fre_clust;
	f_getfree("", &fre_clust, &pfs);

	fresult = f_open(&fil, "lists.txt", FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
	uint32_t file_id = f_size(&fil);
	for (unsigned n = 0; n <= file_id; n++) f_putc('1', &fil);
	fresult = f_close(&fil);

	char file_name[16];
	sprintf(file_name, "log%05u.txt", (unsigned)file_id);

	/* Open file to write/ create a file if it doesn't exist */
	fresult = f_open(&fil, file_name, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);

#ifdef DEBUG
	// uint32_t total = (uint32_t)((pfs->n_fatent - 2) * pfs->csize * 0.5);
	//  uint	32_t free_space = (uint32_t)(fre_clust * pfs->csize * 0.5);
	//
	//  printf("File opened: %s, total: %d, free: %d, %d\n",
	//		  file_name, total, free_space, fresult);
	printf("File: %s, %d\n", file_name, fresult);
#endif

	return fresult == FR_OK;
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &htim14) {
#ifndef DEBUG
    	HAL_IWDG_Refresh(&hiwdg);
#endif
    }
}

void CAN_Received() {

	switch (can.rx.id) {
#ifdef LAUNCHER
	case 'B':
		tlm_launcher.entries[0].set('V', can.rx.get('P', 0, 0.0f));
		tlm_launcher.size = 1;
		break;
	case 'P':
		tlm_nav.entries[0].set('O', can.rx.get('O', 0, 0.0f));
		tlm_nav.entries[1].set('A', can.rx.get('A', 0, 0.0f));
		tlm_nav.entries[2].set('H', can.rx.get('H', 0, 0.0f));
		tlm_nav.entries[3].set('P', can.rx.get('P', 0, 0.0f));
		tlm_nav.size = 4;
		break;
	case 'M':
		tlm_mode = can.rx;
		tlm_mode.id = 'm';
		break;
	case 'S':
		tlm_settings.entries[0].set('I', can.rx.get('I', 0,
				tlm_settings.entries[0].payload.float_));
		tlm_settings.entries[1].set('S', can.rx.get('S', 0,
				tlm_settings.entries[1].payload.float_));
		tlm_settings.entries[2].set('A', can.rx.get('A', 0,
				tlm_settings.entries[2].payload.float_));
		tlm_settings.entries[3].set('Q', can.rx.get('Q', 0,
				tlm_settings.entries[3].payload.float_));
		tlm_settings.size = 4;
		break;
#endif
#ifdef GS
	case 'm':
		command_mode = can.rx;
		break;
	case 's':
		command_settings = can.rx;
		send_settings = true;
		break;
#endif
	}


	if (file_opened) {
		can.rx.addTimestamp(HAL_GetTick());
		sd.tx.push(can.rx);
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
  MX_TIM14_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_Base_Start_IT(&htim14);


#ifdef DEBUG
  printf("Start\n");
#endif

  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);


  file_opened = SD_Init();


  // Reset TWELITE
  HAL_GPIO_WritePin(TWE_NRST_GPIO_Port, TWE_NRST_Pin, GPIO_PIN_RESET);
  HAL_Delay(100);
  HAL_GPIO_WritePin(TWE_NRST_GPIO_Port, TWE_NRST_Pin, GPIO_PIN_SET);


#ifdef LORA_SETUP
  LoRa_Setup();
#else
  lora.begin();
#endif
  lora.startOperation();

  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//	  printf("%d %d %d\n", count0, count1, count0 + count1);

#ifdef LAUNCHER
	  if (tlm_state == TlmState::Init && lora.readyToSend()) {
		  lora.send(PANID, DEST_ADDR, tlm_nav);
		  lora_last_send_tick = HAL_GetTick();

		  ChangeState(TlmState::SendingNav);
	  }
	  else if (tlm_state == TlmState::WaitingUplink &&
			  HAL_GetTick() - tlm_state_tick >= UPLINK_WAIT_TICK) {
		  ChangeState(tlm_state = TlmState::Init);
	  }
	  else if (tlm_state == TlmState::ConfirmingSettings &&
			  HAL_GetTick() - tlm_state_tick >= SETTING_CONFIRM_TICK) {
		  lora.send(PANID, DEST_ADDR, tlm_settings);
		  lora_last_send_tick = HAL_GetTick();

		  ChangeState(TlmState::SendingSettings);
	  }
#endif

	  if (lora.isSending()) {
		  int8_t code = lora.getResponse();

		  // LoRa complete sending
		  if (code >= 0) {
			  Blink();
#ifdef DEBUG
			  printf("LoRa Sent: %d\n", code);
#endif

#ifdef LAUNCHER
			  if (lora.readyToSend()) {
				  switch (tlm_state) {
				  case TlmState::SendingNav:
					  lora.send(PANID, DEST_ADDR, tlm_mode);
					  lora_last_send_tick = HAL_GetTick();

					  ChangeState(TlmState::SendingMode);
					  break;
				  case TlmState::SendingMode:
					  lora.send(PANID, DEST_ADDR, tlm_launcher);
					  lora_last_send_tick = HAL_GetTick();

					  ChangeState(TlmState::SendingLauncher);
					  break;
				  case TlmState::SendingLauncher:
					  ChangeState(TlmState::WaitingUplink);
					  break;
				  case TlmState::SendingSettings:
					  ChangeState(TlmState::Init);
					  break;
				  default:
					  ChangeState(TlmState::Init);
				  }
			  }
			  else ChangeState(TlmState::Init);
#endif

			  Command tlm('S', 0, 0, 3);
			  tlm.entries[0].set('C', (int32_t)code);
			  tlm.entries[1].set('O', (uint32_t)lora.tx_ok_count);
			  tlm.entries[2].set('N', (uint32_t)lora.tx_ng_count);

			  can.tx.push(tlm);
			  CAN_Send();

			  if (file_opened) {
				  tlm.addTimestamp(HAL_GetTick());
				  sd.tx.push(tlm);
			  }
		  }
		  else if (HAL_GetTick() - lora_last_send_tick >= LORA_TIMEOUT_TICK) {
#ifdef DEBUG
			  printf("LoRa Reset");
#endif
			  lora.begin();
		  }
	  }
	  else if (lora.inOperation()) {
		  Command rx;
		  bool received = lora.receive(rx);

		  // LoRa received
		  if (received) {
			  Blink();
#ifdef DEBUG
			  printf("LoRa Received %d: %c (%d)\n", lora.rssi, rx.id, rx.size);
#endif
#ifdef LAUNCHER
			  if (tlm_state == TlmState::WaitingUplink) {
				  if (rx.id == 's') {
					  ChangeState(TlmState::ConfirmingSettings);
				  }
				  else {
					  ChangeState(TlmState::Init);
				  }
			  }

			  rx.from = 'G';
#endif
#ifdef GS
			  if (rx.id == 'l') {
				  if (send_settings) {
					  lora.send(PANID, DEST_ADDR, command_settings);
					  send_settings = false;
				  }
				  else {
					  lora.send(PANID, DEST_ADDR, command_mode);
				  }

				  lora_last_send_tick = HAL_GetTick();
			  }
			  rx.from = 'L';
#endif
			  can.tx.push(rx);

			  Command tlm('R', 0, 0, 2);
			  tlm.entries[0].set('R', (int32_t)lora.rssi);
			  tlm.entries[1].set('C', (uint32_t)lora.rx_count);
			  can.tx.push(tlm);
			  CAN_Send();

			  if (file_opened) {
				  rx.addTimestamp(HAL_GetTick());
				  tlm.addTimestamp(HAL_GetTick());
				  sd.tx.push(rx);
				  sd.tx.push(tlm);
			  }
		  }
	  }

	  if (sd.isSending()) {
		  uint8_t buf[14];
		  uint8_t len;

		  while (true) {
			  int remains = sd.send(buf, len);

			  if (len == 0) continue;

			  f_puts((char*)buf, &fil);

			  if (remains == 0) break;
		  }
	  }

	  if (file_opened && HAL_GetTick() - sd_last_sync_tick >= SD_SYNC_TICK){
		  f_sync(&fil);
		  sd_last_sync_tick = HAL_GetTick();
	  }

	  if (can.isSending() &&
			  HAL_GetTick() - can_last_send_tick >= CAN_SEND_TIMEOUT_TICK) {
		  can.cancelSending();
#ifdef DEBUG
		  printf("TIMEOUT\n");
#endif
	  }


	  if (HAL_GetTick() - blink_tick > BLINK_TICK) {
		  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
	  }

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
  hcan.Init.Prescaler = 24;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_12TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_3TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = ENABLE;
  hcan.Init.ReceiveFifoLocked = ENABLE;
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
  htim14.Init.Prescaler = 48000;
  htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim14.Init.Period = 1000;
  htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim14.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim14) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM14_Init 2 */
//  htim14.Init.Period = 1000 / SAMPLE_FREQ;
  /* USER CODE END TIM14_Init 2 */

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
  huart2.Init.BaudRate = LORA_BAUD;
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
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(LORA_NRST_GPIO_Port, LORA_NRST_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, LORA_NSLEEP_Pin|TWE_NRST_Pin, GPIO_PIN_SET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, TWE_NSLEEP_Pin|TWE_NPGM_Pin, GPIO_PIN_SET);

	/*Configure GPIO pin : LORA_NRST_Pin */
	GPIO_InitStruct.Pin = LORA_NRST_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LORA_NRST_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : LED_Pin */
	GPIO_InitStruct.Pin = LED_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : SD_NSW_Pin */
	GPIO_InitStruct.Pin = SD_NSW_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(SD_NSW_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : LORA_NSLEEP_Pin TWE_NRST_Pin */
	GPIO_InitStruct.Pin = LORA_NSLEEP_Pin|TWE_NRST_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  /*Configure GPIO pins : TWE_NSLEEP_Pin TWE_NPGM_Pin */
	GPIO_InitStruct.Pin = TWE_NSLEEP_Pin|TWE_NPGM_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/* USER CODE BEGIN 4 */

void Blink() {
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
	blink_tick = HAL_GetTick();
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	/* Get RX message */
	if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &CanRxHeader, CanRxData) != HAL_OK) {
		/* Reception Error */
		Error_Handler();
	}

	if (can.receive(CanRxHeader.StdId, CanRxData, CanRxHeader.DLC)) {
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
		CAN_Received();
	}
}


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
				return;
			}
		}

		tick = HAL_GetTick();

		while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan) != 3) {
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
