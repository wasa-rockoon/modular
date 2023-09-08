/*
 * es920lr.hpp
 *
 *  Created on: Sep 8, 2022
 *      Author: yuuki.fj
 */

#ifndef INC_ES920LR_HPP_
#define INC_ES920LR_HPP_

#include "uart.hpp"


class ES920LR: public UART {
public:
	ES920LR(UART_HandleTypeDef& huart, uint8_t* buf,
      unsigned ring_size, unsigned tail_size);

	bool begin(bool reset = true);
	bool config(uint8_t command, const char parameter[], uint8_t len);
	bool startOperation();

	int8_t getResponse();

	unsigned receive(uint8_t*& data, uint16_t& panid, uint16_t& addr);
	unsigned receive(uint8_t*& data);

	bool send(const char panid[4], const char destid[4], const uint8_t* buf, uint8_t len);

	inline bool inOperation() { return in_operation_; }
	inline bool isSending() { return is_sending_; }
	inline bool readyToSend() { return in_operation_ && !is_sending_; }

	int16_t rssi;
	uint32_t tx_ok_count;
	uint32_t tx_ng_count;
	uint32_t rx_count;

private:
	bool waitConfigResponse();

	bool in_operation_;
	bool is_sending_;

	int16_t read4Hex();
};



#endif /* INC_ES920LR_HPP_ */
