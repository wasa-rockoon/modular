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

ES920LR::ES920LR(UART_HandleTypeDef& huart, uint8_t* buf,
    unsigned ring_size, unsigned tail_size)
  : UART(huart, buf, ring_size, tail_size) {
	in_operation_ = false;
	is_sending_ = false;

	rssi = -255;
	tx_ok_count = 0;
	tx_ng_count = 0;
	rx_count = 0;
}

bool ES920LR::begin(bool reset) {
  bool ok = UART::begin();

	HAL_Delay(100);

	if (reset) {
		HAL_GPIO_WritePin(LORA_NRST_GPIO_Port, LORA_NRST_Pin, GPIO_PIN_RESET);
		HAL_Delay(100);
		HAL_GPIO_WritePin(LORA_NRST_GPIO_Port, LORA_NRST_Pin, GPIO_PIN_SET);

		HAL_Delay(3000);

		if (rxIsEmpty()) return false;

		clear();

		uint8_t com_processor[] = "2\x0d\x0a";
		write(com_processor, 3);

		return waitConfigResponse();
	}
	else {
		clear();
		return ok;
	}

}

bool ES920LR::startOperation() {
	HAL_Delay(10);

	uint8_t com_start[] = "z\x0d\x0a";
	write(com_start, 3);

	in_operation_ = waitConfigResponse();
	is_sending_ = false;

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

		write(com, 3);
	}
	else {
		uint8_t com[8];
		com[0] = command;
		com[1] = ' ';
		strncpy((char*)com + 2, (const char*)parameter, len);
		com[2 + len] = '\x0d';
		com[3 + len] = '\x0a';

		write(com, 4 + len);
	}

	return waitConfigResponse();
}

bool ES920LR::waitConfigResponse() {
  while (available() < 4);

	uint8_t *response = read(4);
	if (strncmp((const char*)response, "OK\x0d\x0a", 4) == 0) {
		return true;
	}
	else {
		HAL_Delay(10);
		clear();
		return false;
	}
}


bool ES920LR::send(const char panid[], const char destid[], const uint8_t* buf, uint8_t len) {
	if (is_sending_) return false;

	clear();

	uint8_t header[128];
	header[0] = len + 8;
	strncpy((char*)header+ 1, panid, 4);
	strncpy((char*)header+ 5, destid, 4);
	memcpy(header + 9, buf, len);

	write(header, 9 + len);
//	write(buf, len);

	is_sending_ = true;

	return true;
}

int8_t ES920LR::getResponse() {
	if (!is_sending_ || rxIsEmpty()) return -1;

	unsigned len = peek();

  if (available() < len + 1) return -1;

  len = read();

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

unsigned ES920LR::receive(uint8_t*& data) {
  uint16_t panid;
  uint16_t addr;
  return receive(data, panid, addr);
}

unsigned ES920LR::receive(uint8_t*& data, uint16_t& panid, uint16_t& addr) {
	if (!in_operation_ || is_sending_ || rxIsEmpty()) return 0;

	volatile uint8_t len = peek();

	if (available() < len + 13) return 0;

	len = read();
	rssi  = read4Hex();
	panid = read4Hex();
	addr  = read4Hex();
	rx_count++;

	data = read(len - 12);

	return len - 12;
}

int16_t ES920LR::read4Hex() {
	char hex[5];
	for (int n = 0; n < 4; n++) hex[n] = read();
	hex[4] = '\0';

	long num = strtol(hex, nullptr, 16);
	if (num >= 32768) num -= 65536;
	return (int16_t)num;
}


