/*
 * uart.hpp
 *
 *  Created on: Aug 19, 2022
 *      Author: yuuki.fj
 */

#ifndef INC_UART_HPP_
#define INC_UART_HPP_

#include "main.h"

#define RXBUFSIZE 32
#define TXBUFSIZE 5


class UART {
public:
	UART(UART_HandleTypeDef& huart);

	bool rx_empty();
	uint32_t available();

	uint32_t read(uint8_t*& buf);

	inline uint8_t* rx_buf() { return rx_buf_; }
	inline uint8_t* tx_buf() { return tx_buf_; }

private:
	UART_HandleTypeDef& huart_;

	uint8_t rx_buf_[RXBUFSIZE];
	uint8_t tx_buf_[TXBUFSIZE];

	uint32_t rx_read_ptr_;

	uint32_t rx_write_ptr();
};



#endif /* INC_UART_HPP_ */
