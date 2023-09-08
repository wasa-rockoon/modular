/*
 * uart.cpp
 *
 *  Created on: Aug 19, 2022
 *      Author: yuuki.fj
 */

#include "uart.hpp"

#include <cstring>

UART::UART(UART_HandleTypeDef& huart, uint8_t* buf,
    unsigned ring_size, unsigned tail_size):
	huart_(huart), buf_(buf), ring_size_(ring_size), tail_size_(tail_size),
	rx_read_ptr_(0) {};

bool UART::begin() {
  return HAL_UART_Receive_DMA(&huart_, buf_, ring_size_) == HAL_OK;
}

unsigned UART::rx_write_ptr() {
  return (ring_size_ - huart_.hdmarx->Instance->CNDTR) % ring_size_;
};

unsigned UART::available() {
	return (rx_write_ptr() + ring_size_ - rx_read_ptr_) % ring_size_;
};

int16_t UART::read() {
	if (rxIsEmpty()) return -1;

	uint8_t c = buf_[rx_read_ptr_];

	rx_read_ptr_++;
	if (rx_read_ptr_ == ring_size_) rx_read_ptr_ = 0;

	return c;
}

int16_t UART::peek(unsigned pos) {
  if (rxIsEmpty()) return -1;

  return buf_[(rx_read_ptr_ + pos) % ring_size_];
}


uint8_t* UART::read(unsigned len) {
  if (len > available()) return nullptr;

  unsigned ptr = rx_read_ptr_;

  if (ptr + len >= ring_size_) {
    std::memcpy(buf_ + ring_size_, buf_, ptr + len - ring_size_);
    rx_read_ptr_ = ptr + len - ring_size_;
  }
  else {
    rx_read_ptr_ += len;
  }

  return buf_ + ptr;
}


void UART::clear() {
	rx_read_ptr_ = rx_write_ptr();
}

void UART::changeBaudRate(unsigned baud) {
  HAL_UART_Abort_IT(&huart_);
  HAL_UART_DeInit(&huart_);
  huart_.Init.BaudRate = baud;
  if (HAL_UART_Init(&huart_) != HAL_OK) {
      Error_Handler();
  }
  HAL_UART_Receive_DMA(&huart_, buf_, ring_size_);

//  huart_.Instance->CR1 &= ~(USART_CR1_UE);
//  huart_.Instance->BRR = UART_BRR_SAMPLING8(HAL_RCC_GetPCLK2Freq(), baud);
//  huart_.Instance->CR1 |= USART_CR1_UE;
}

