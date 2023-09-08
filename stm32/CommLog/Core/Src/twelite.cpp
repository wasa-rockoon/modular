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

TWELITE::TWELITE(UART_HandleTypeDef& huart, uint8_t* buf,
    unsigned ring_size, unsigned tail_size)
  : UART(huart, buf, ring_size, tail_size) {
	lqi_ = -1;
}

bool TWELITE::begin(bool reset) {
  bool ok = UART::begin();
	HAL_Delay(10);


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

		return ok;
	}
	else {
		clear();
		return ok;
	}
}

bool TWELITE::interactiveMode() {
	HAL_Delay(10);
	uint8_t com[] = "+";
	write(com, 1);
	HAL_Delay(500);
	write(com, 1);
	HAL_Delay(500);
	write(com, 1);

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

		write(com, 2);
	}
	else {
		uint8_t com[32];
		com[0] = command;
		strncpy((char*)com + 1, (const char*)parameter, len);
		com[len + 1] = '\n';

		write(com, 2 + len);
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


bool TWELITE::send(const uint8_t* data, unsigned len) {

	if (huart_.hdmatx->State != HAL_DMA_STATE_READY) {
#ifdef DEBUG
	  printf("BUSY");
#endif
	  return false;
	}

	uint16_t ex_len = len + 4;
	uint16_t data_len = 0x8000 + ex_len;

	uint8_t header[8];

	header[0] = 0xA5;
	header[1] = 0x5A;
	header[2] = data_len >> 8;
	header[3] = data_len & 0xFF;
	header[4] = dest_id_;
	header[5] = 0xA0;
	header[6] = 0x00;
	header[7] = 0xFF;

	uint8_t check_sum = 0;
	for (unsigned i = 4; i < 8; i++) {
		check_sum ^= header[i];
	}
  for (unsigned i = 0; i < len; i++) {
    check_sum ^= data[i];
  }

  write(header, 8);
  write(data, len);
  write(&check_sum, 1);

	return true;
}



unsigned TWELITE::receive(uint8_t*& data) {
  if (available() < 4) return 0;

  if (peek(0) != 0xA5 || peek(1) != 0x5A) {
    error();
#ifdef DEBUG
    printf("INVALID\n");
#endif
    clear();
    return 0;
  }

  uint16_t ex_len = (((uint16_t)peek(2) & 0x7F) << 8) + peek(3);

  uint8_t* buf = read(6 + ex_len);

  if (buf == nullptr) return 0;

  uint8_t check_sum = 0;

  for (int i = 0; i < ex_len; i++) {
    check_sum ^= buf[4 + i];
  }


  if (check_sum != buf[4 + ex_len] || buf[5 + ex_len] != 0x04) {
    error();
    clear();
  #ifdef DEBUG
    printf("CHECKSUM %X != %X\n", check_sum, buf[4 + ex_len]);
  #endif
    return 0;
  }
  else if (buf[4] == 0xDB) { // ACK message
    uint8_t ack_id = buf[6];
    bool ok = buf[7] == 1;
    if (buf[5] != 0xA1 || !ok) error();
    else sent_count_++;
  #ifdef DEBUG
    printf("ACK %d\n", ok);
  #endif
    return 0;
  }
  else if (buf[4] <= 0x64 || buf[4] == 0x78) { // Receive
    if (buf[5] != 0xA0) {
      error();
      clear();
  #ifdef DEBUG
      printf("ERROR");
  #endif
      return 0;
    }
    else {
//      uint8_t ack_id = buf[6];
      lqi_ = buf[15];
      unsigned len = ((uint16_t)buf[16] << 8) + buf[17];

      received_count_++;
      data = buf + 18;
      return len;
    }
  }
  else {
    error();
    clear();
    return 0;
  }
}


