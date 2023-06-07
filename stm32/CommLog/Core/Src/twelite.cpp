/*
 * twelite.cpp
 *
 *  Created on: Feb 24, 2023
 *      Author: yuuki.fj
 */


/*
 * TWELITE.cpp
 *
 *  Created on: Sep 8, 2022
 *      Author: yuuki.fj
 */

#include "twelite.hpp"

#include "main.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

TWELITE::TWELITE(UART_HandleTypeDef& huart): UART(huart) {
	lqi_ = -1;
}

bool TWELITE::begin(bool reset) {
	HAL_Delay(10);

	HAL_UART_Receive_DMA(&huart_, this->rx_buf_, RXBUFSIZE);

	HAL_GPIO_WritePin(TWE_NRST_GPIO_Port, TWE_NRST_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(TWE_NPGM_GPIO_Port, TWE_NPGM_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(TWE_NSLEEP_GPIO_Port, TWE_NSLEEP_Pin, GPIO_PIN_SET);

	if (reset) {
		HAL_Delay(100);
		HAL_GPIO_WritePin(TWE_NRST_GPIO_Port, TWE_NRST_Pin, GPIO_PIN_RESET);
		HAL_Delay(100);
		HAL_GPIO_WritePin(TWE_NRST_GPIO_Port, TWE_NRST_Pin, GPIO_PIN_SET);
		HAL_Delay(100);

		if (rxIsEmpty()) return false;

		clear();

		return true;
	}
	else {
		clear();
		return true;
	}
}

bool TWELITE::interactiveMode() {
	HAL_Delay(10);
	uint8_t com[] = "+";
	HAL_UART_Transmit_DMA(&huart_, com, 1);
	HAL_Delay(500);
	HAL_UART_Transmit_DMA(&huart_, com, 1);
	HAL_Delay(500);
	HAL_UART_Transmit_DMA(&huart_, com, 1);

	if (rxIsEmpty()) return false;
	clear();
	return true;
}


bool TWELITE::config(uint8_t command, const char parameter[]) {
	HAL_Delay(10);

	unsigned len = strlen(parameter);

	if (len == 0) {
		uint8_t com[2];
		com[0] = command;
		com[1] = '\n';

		HAL_UART_Transmit_DMA(&huart_, com, 2);
	}
	else {
		uint8_t com[32];
		com[0] = command;
		strncpy((char*)com + 1, (const char*)parameter, len);
		com[len + 1] = '\n';

		HAL_UART_Transmit_DMA(&huart_, com, 2 + len);
	}

	HAL_Delay(10);

	if (rxIsEmpty()) return false;
	clear();
	return true;
}

bool TWELITE::saveConfig() {
	config('S', "");
	HAL_Delay(100);
	clear();
	return true;
}


bool TWELITE::update(Command &message) {
	send();
	bool received = receive();
	if (received) message = channel_.rx;
	return received;
}

void TWELITE::send(const Command &message) {
	if (channel_.tx.isFull()) {
		channel_.tx.pop();
		dropped_count_++;
	}
	channel_.tx.push(message);
	send();
}



void TWELITE::send() {
	unsigned len;

	while ((len = channel_.nextWriteSize()) > 0) {
	    if (huart_.hdmatx->State != HAL_DMA_STATE_READY) {
#ifdef DEBUG
	      printf("BUSY");
#endif
	      return;
	    }

		len = channel_.write(tx_buf_ + 8);

		uint16_t ex_len = len + 4;
		uint16_t data_len = 0x8000 + ex_len;

		tx_buf_[0] = 0xA5;
		tx_buf_[1] = 0x5A;
		tx_buf_[2] = data_len >> 8;
		tx_buf_[3] = data_len & 0xFF;

		tx_buf_[4] = dest_id_;
		tx_buf_[5] = 0xA0;
		tx_buf_[6] = channel_.tx.first().id;
		tx_buf_[7] = 0xFF;

		uint8_t check_sum = 0;
		for (int i = 0; i < ex_len; i++) {
		  check_sum ^= tx_buf_[i + 4];
		}
		tx_buf_[4 + ex_len] = check_sum;

		HAL_UART_Transmit_DMA(&huart_, tx_buf_, ex_len + 5);
	}
}



bool TWELITE::receive() {
	while (available() > 0) {
		rx_buf_[rx_count_] = read();
#ifdef DEBUG
		printf("%02X", rx_buf_[rx_count_]);
#endif
		rx_count_++;

		if (rx_count_ >= TWE_BUF_SIZE) {
		  error();
		  rx_count_ = 0;
#ifdef DEBUG
		  printf("OVERFLOW\n");
#endif
		}

		if (rx_count_ < 4) continue;

		if (rx_buf_[0] != 0xA5 || rx_buf_[1] != 0x5A) {
		  error();
		  rx_count_ = 0;
#ifdef DEBUG
		  printf("INVALID\n");
#endif
		  continue;
		}

		uint16_t ex_len = (((uint16_t)rx_buf_[2] & 0x7F) << 8) + rx_buf_[3];

		if (rx_count_ < 6 + ex_len) continue;

		uint8_t buf[TWE_BUF_SIZE];

		uint8_t check_sum = 0;

		for (int i = 0; i < ex_len; i++) {
		  buf[i] = rx_buf_[4 + i];
		  check_sum ^= buf[i];
		}

		if (check_sum != rx_buf_[4 + ex_len] || rx_buf_[5 + ex_len] != 0x04) {
		  error();
#ifdef DEBUG
		  printf("CHECKSUM %X != %X\n", check_sum, rx_buf_[4 + ex_len]);
#endif
		}
		else if (buf[0] == 0xDB) { // ACK message
		  uint8_t ack_id = buf[2];
		  bool ok = buf[3] == 1;
		  if (buf[1] != 0xA1 || !ok) error();
		  else sent_count_++;
#ifdef DEBUG
		  printf("ACK %d\n", ok);
#endif
		}
		else if (buf[0] <= 0x64 || buf[0] == 0x78) { // Receive
		  if (buf[1] != 0xA0) {
			error();
#ifdef DEBUG
			printf("ERROR");
#endif
		  }
		  else {
			uint8_t ack_id = buf[2];
			lqi_ = buf[11];
			unsigned len = ((uint16_t)buf[12] << 8) + buf[13];

//			printf("RX %d\n", len);

			rx_count_ = 0;

			if (channel_.read(buf + 14, len)) {
				received_count_++;
				return true;
			}
		  }
		}
		else {
		  error();
		}

		rx_count_ = 0;
	}

	return false;
}


