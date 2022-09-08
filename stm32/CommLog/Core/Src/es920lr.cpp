/*
 * es920lr.cpp
 *
 *  Created on: Sep 8, 2022
 *      Author: yuuki.fj
 */

#include "es920lr.hpp"

#include "main.h"
#include <string.h>

ES920LR::ES920LR(UART_HandleTypeDef& huart): UART(huart) {
	in_operation_ = false;
}

bool ES920LR::begin() {
	HAL_UART_Receive_DMA(&huart2, lora.rx_buf(), RXBUFSIZE);

	HAL_GPIO_WritePin(LORA_NRST_GPIO_Port, LORA_NRST_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(LORA_NRST_GPIO_Port, LORA_NRST_Pin, GPIO_PIN_SET);

	HAL_Delay(2000);

	if (rxIsEmpty()) return false;

	clear();

	uint8_t com_processor[] = "2\x0d\x0a";
	HAL_UART_Transmit_DMA(&huart2, com_processor, 3);

	return waitConfigResponse();
}

bool ES920LR::startOperation() {
	uint8_t com_start[] = "z\x0d\x0a";
	HAL_UART_Transmit_DMA(&huart2, com_start, 3);

	in_operation_ = waitConfigResponse();
	return in_operation_;
}

bool ES920LR::config(uint8_t command, const uint8_t parameter[], uint8_t len) {
	uint8_t com[7];
	com[0] = command;
	com[1] = ' ';
	strcpy(com + 2, parameter);
	com[2 + len] = '\x0d';
	com[3 + len] = '\x0a';

	HAL_UART_Transmit_DMA(&huart, com, 4 + len);

	return waitConfigResponse();
}

bool waitConfigResponse() {
	uint8_t response[4];
	for (int n = 0; n < 4; n++) {
		while (rxIsEmpty());
		response[n] = read();
	}
	if (strcmp(response, "OK\x0d\x0a") == 0) {
		return true;
	}
	else {
		clear();
		return false;
	}
}


