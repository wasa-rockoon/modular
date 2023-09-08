/*
 * app.h
 *
 *  Created on: Jul 30, 2023
 *      Author: yuuki.fj
 */

#ifndef INC_APP_H_
#define INC_APP_H_


#include "main.h"

#define LAUNCHER 0x02
#define GS1 0x06
#define GS2 0x05

#define UNIT LAUNCHER
//#define UNIT GS2


#if UNIT == LAUNCHER
#define LORA
//#define LORA_RX
#elif UNIT == GS1 || UNIT == GS2
#define LORA
//#define LORA_TX
#endif

// #define LORA_SETUP
// #define TWE_SETUP


#define NODE 'C'

const char PANID[] = "0110";

#if (UNIT == LAUNCHER)
const char OWN_ID[]    = "0002";
const char DEST_ADDR[] = "FFFF";

#elif (UNIT == GS1)
const char OWN_ID[]    = "0006";
const char DEST_ADDR[] = "0002";

#elif (UNIT == GS2)
const char OWN_ID[]    = "0005";
const char DEST_ADDR[] = "0002";
#endif

#define ES920_CHANNEL "15"

#define TWE_APP_ID "57415341"
#define TWE_DEV_ID "120"
#define TWE_CHANNEL "12,18,25"
#define TWE_DEST_ID 0

#define TWE_BAUD 115200
#define LORA_BAUD 38400


#define BLINK_TICK 500

#define TWELITE_BUF_SIZE 128
#define TWELITE_PACKET_SIZE_MAX 128

#if UNIT == LAUNCHER

#define LORA_BUF_SIZE    16
#define LORA_PACKET_SIZE_MAX 16

#elif UNIT == GS1 || UNIT == GS2

#define LORA_BUF_SIZE    32
#define LORA_PACKET_SIZE_MAX 0

#endif


#define TLM_FREQ 1

#define SD_SYNC_FREQ 0.1



#ifdef __cplusplus
extern "C" {
#endif

extern CAN_HandleTypeDef hcan;

extern IWDG_HandleTypeDef hiwdg;

extern SPI_HandleTypeDef hspi2;

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;


extern void setup();
extern void loop();

#ifdef __cplusplus
};
#endif


#endif /* INC_APP_H_ */
