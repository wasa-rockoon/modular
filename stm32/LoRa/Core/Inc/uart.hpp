/*
 * uart.hpp
 *
 *  Created on: Aug 19, 2022
 *      Author: yuuki.fj
 */

#ifndef INC_UART_HPP_
#define INC_UART_HPP_

#include "main.h"

class UART {
public:
	UART(UART_HandleTypeDef& huart, uint8_t* buf,
	    unsigned ring_size, unsigned tail_size);

	bool begin();

	bool rxIsEmpty() {
	  return rx_read_ptr_ == rx_write_ptr();
	}
	unsigned available();

	inline bool write(const uint8_t* buf, unsigned len) {
	  while (huart_.gState != HAL_UART_STATE_READY);
//	  HAL_Delay(1);
	  return HAL_UART_Transmit_DMA(&huart_, buf, len) == HAL_OK;
	}
	inline bool write(uint8_t c) {
	  while (huart_.gState != HAL_UART_STATE_READY);
//	  HAL_Delay(1);
	  return HAL_UART_Transmit_DMA(&huart_, &c, 1) == HAL_OK;
	}

	int16_t read();
	int16_t peek(unsigned pos = 0);
	uint8_t* read(unsigned len);

	void clear();

	void changeBaudRate(unsigned baud);


protected:
	UART_HandleTypeDef& huart_;

	uint8_t* buf_;
	unsigned ring_size_;
	unsigned tail_size_;

	unsigned rx_read_ptr_;

	unsigned rx_write_ptr();
};



#endif /* INC_UART_HPP_ */
