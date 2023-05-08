/*
 * es920lr.cpp
 *
 *  Created on: Sep 8, 2022
 *      Author: yuuki.fj
 */

#include "es920lr.hpp"

#include "main.h"
#include <string.h>
#include <stdlib.h>
//#include <cstdio>

ES920LR::ES920LR(UART_HandleTypeDef& huart): UART(huart) {
	in_operation_ = false;
	is_sending_ = false;
	response_len_ = -1;
	receiving_len_ = -1;

	rssi = 0;
	tx_ok_count = 0;
	tx_ng_count = 0;
	rx_count = 0;
}

bool ES920LR::begin(bool reset) {
	HAL_Delay(10);

	HAL_UART_Receive_DMA(&huart_, this->rx_buf_, RXBUFSIZE);

	if (reset) {
		HAL_GPIO_WritePin(LORA_NRST_GPIO_Port, LORA_NRST_Pin, GPIO_PIN_RESET);
		HAL_Delay(100);
		HAL_GPIO_WritePin(LORA_NRST_GPIO_Port, LORA_NRST_Pin, GPIO_PIN_SET);

		HAL_Delay(3000);

		if (rxIsEmpty()) return false;

		clear();

		uint8_t com_processor[] = "2\x0d\x0a";
		HAL_UART_Transmit_DMA(&huart_, com_processor, 3);

		return waitConfigResponse();
	}
	else {
		clear();
		return true;
	}

}

bool ES920LR::startOperation() {
	HAL_Delay(10);

	uint8_t com_start[] = "z\x0d\x0a";
	HAL_UART_Transmit_DMA(&huart_, com_start, 3);

	in_operation_ = waitConfigResponse();
	is_sending_ = false;
	response_len_ = -1;
	receiving_len_ = -1;

	HAL_Delay(100);

	clear();

	return in_operation_;
}

bool ES920LR::config(uint8_t command, const char parameter[], uint8_t len) {
	HAL_Delay(10);

	if (len == 0) {
		uint8_t com[7];
		com[0] = command;
		com[1] = '\x0d';
		com[2] = '\x0a';

		HAL_UART_Transmit_DMA(&huart_, com, 3);
	}
	else {
		uint8_t com[8];
		com[0] = command;
		com[1] = ' ';
		strncpy((char*)com + 2, (const char*)parameter, len);
		com[2 + len] = '\x0d';
		com[3 + len] = '\x0a';

		HAL_UART_Transmit_DMA(&huart_, com, 4 + len);
	}

	return waitConfigResponse();
}

bool ES920LR::waitConfigResponse() {
	uint8_t response[5];
	for (int n = 0; n < 4; n++) {
//		while (rxIsEmpty());
		response[n] = read();
	}
	response[4] = '\0';
	if (strcmp((const char*)response, "OK\x0d\x0a") == 0) {
		return true;
	}
	else {
		HAL_Delay(10);
		clear();
		return false;
	}
}

bool ES920LR::send(const char panid[4], const char destid[4], const Command& command) {

	uint8_t* buf = tx_buf();
	buf[0] = command.id;
	buf[1] = command.size;
	uint8_t i = 2;
	for (int n = 0; n < command.size; n++) {
		uint8_t len = command.entries[n].encode(buf + i);
		i += len;
	}

	uint8_t len = i;

	if (is_sending_ || isReceiving()) return false;

	clear();

	tx_buf_[0] = len + 8;
	strncpy((char*)tx_buf_+ 1, panid, 4);
	strncpy((char*)tx_buf_+ 5, destid, 4);

	HAL_UART_Transmit_DMA(&huart_, tx_buf_, 9 + len);
	is_sending_ = true;

	return true;
}

bool ES920LR::receive(Command& command) {
	int8_t len = receive();
	if (len < 2) return false;

	command.id   = read();
	command.size = read();
	command.to   = 0;
	command.from = 0;

	int i = 2;
	for (int n = 0; n < command.size; n++) {
		uint8_t data[5];
		for (int i = 0; i < 5; i++) {
			if (available() == 0) return false;
			data[i] = read();
		}

		i += command.entries[n].decode(data);
	}

	return true;
}


bool ES920LR::send(const char panid[], const char destid[], uint8_t len) {
	if (is_sending_ || isReceiving()) return false;

	clear();

	tx_buf_[0] = len + 8;
	strncpy((char*)tx_buf_+ 1, panid, 4);
	strncpy((char*)tx_buf_+ 5, destid, 4);

	HAL_UART_Transmit_DMA(&huart_, tx_buf_, 9 + len);
	is_sending_ = true;

	return true;
}

int8_t ES920LR::getResponse() {
	if (!is_sending_ || rxIsEmpty()) return -1;

	if (response_len_ == -1) response_len_ = read();

	if ((int8_t)available() < response_len_) return -1;

	uint8_t len = response_len_;

	response_len_ = -1;
	is_sending_ = false;

	uint8_t res[2];
	res[0] = read();
	res[1] = read();

	if (res[0] == 'O' && res[1] == 'K') {
		tx_ok_count++;
		return 0;
	}

	if (len != 6) {
		clear();
		tx_ng_count++;
		return 110;
	}

	char code[3];
	read();
	code[0] = read();
	code[1] = read();
	code[2] = read();

	tx_ng_count++;

	return atoi(code);
}

int8_t ES920LR::receive() {
	uint16_t panid;
	uint16_t addr;
	return receive(panid, addr);
}

int8_t ES920LR::receive(uint16_t& panid, uint16_t& addr) {
	if (!in_operation_ || is_sending_ || rxIsEmpty()) return -1;

	if (receiving_len_ == -1) receiving_len_ = read();

	if ((int)available() < receiving_len_) return -1;

	int8_t len = receiving_len_ - 8;

	if (len < 0) {
		clear();
		return -1;
	}

	receiving_len_ = -1;

	rssi = read4Hex();
	panid = read4Hex();
	addr = read4Hex();
	rx_count++;

//	for (int n = 0; n < len; n++) rx_buf_[n] = read();

	return len;
}

int16_t ES920LR::read4Hex() {
	char hex[5];
	for (int n = 0; n < 4; n++) hex[n] = read();
	hex[4] = '\0';

	long num = strtol(hex, nullptr, 16);
	if (num >= 32768) num -= 65536;
	return (int16_t)num;
}


