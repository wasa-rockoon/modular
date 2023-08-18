/*
 * app.h
 *
 *  Created on: Aug 2, 2023
 *      Author: yuuki.fj
 */

#ifndef INC_APP_H_
#define INC_APP_H_

#include "main.h"

#define LAUNCHER 0x02
#define GS1 0x06
#define GS2 0x05

#define SYSTEM LAUNCHER
//#define SYSTEM GS1

#define ROCKOON_ADDR 0x5753

#define LAUNCHER_TLM_CHANNEL 15
#define LAUNCHER_CMD_CHANNEL 17
#define ROCKET_TLM_CHANNEL 19

#define NODE 'R'

#define LORA_BUF_SIZE    256
#define LORA_PACKET_SIZE_MAX 32

#define BLINK_MS 50

#ifdef __cplusplus
extern "C" {
#endif

extern CAN_HandleTypeDef hcan;

extern IWDG_HandleTypeDef hiwdg;

extern TIM_HandleTypeDef htim14;

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;

extern void setup();
extern void loop();

#ifdef __cplusplus
};
#endif


#endif /* INC_APP_H_ */
