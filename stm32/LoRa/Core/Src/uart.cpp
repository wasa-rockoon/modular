/*
 * uart.cpp
 *
 *  Created on: Aug 19, 2022
 *      Author: yuuki.fj
 */

#include "uart.hpp"

UART::UART(UART_HandleTypeDef& huart):
	huart_(huart), rx_read_ptr_(0) {};

uint32_t UART::rx_write_ptr() {
	return (RXBUFSIZE - huart_.hdmarx->Instance->CNDTR) & (RXBUFSIZE - 1);
};

bool UART::rxIsEmpty() {
	return rx_read_ptr_ == rx_write_ptr();
}

uint32_t UART::available() {
	return (rx_write_ptr() + RXBUFSIZE - rx_read_ptr_) % RXBUFSIZE;
};

uint8_t UART::read() {
	uint32_t write_ptr = rx_write_ptr();

	if (rx_read_ptr_ == write_ptr) return 0;

	uint8_t c = rx_buf_[rx_read_ptr_];

	rx_read_ptr_++;
	if (rx_read_ptr_ == RXBUFSIZE) rx_read_ptr_ = 0;

	return c;
}

uint32_t UART::read(uint8_t*& buf) {
	uint32_t write_ptr = rx_write_ptr();
	buf = rx_buf_+ rx_read_ptr_;

	if (rx_read_ptr_<= write_ptr) {
		uint32_t len = write_ptr - rx_read_ptr_;
		rx_read_ptr_ = write_ptr;
		return len;
	}
	else {
		uint32_t len = RXBUFSIZE - 1 - rx_read_ptr_;
		rx_read_ptr_ = 0;
		return len;
	}
}

void UART::clear() {
	rx_read_ptr_ = rx_write_ptr();
}
