/*
 * es920lr.hpp
 *
 *  Created on: Sep 8, 2022
 *      Author: yuuki.fj
 */

#ifndef INC_ES920LR_HPP_
#define INC_ES920LR_HPP_

#include "uart.hpp"
#include "command.hpp"

class ES920LR: public UART {
public:
	ES920LR(UART_HandleTypeDef& huart);

	bool begin(bool reset = true);
	bool config(uint8_t command, const char parameter[], uint8_t len);
	bool startOperation();

	bool send(const char panid[4], const char destid[4], const Command& command);
	int8_t getResponse();
	bool receive(Command& command);

	bool send(const char panid[4], const char destid[4], uint8_t len);
	int8_t receive();
	int8_t receive(uint16_t& panid, uint16_t& addr);

	inline uint8_t* tx_buf() { return tx_buf_ + 9; }
	inline uint8_t* rx_buf() { return rx_buf_; }
	inline bool inOperation() { return in_operation_; }
	inline bool isSending() { return is_sending_; }
	inline bool isReceiving() { return receiving_len_ != -1; }
	inline bool readyToSend() { return in_operation_ && !is_sending_ && !isReceiving(); }

	int16_t rssi;
	uint32_t tx_ok_count;
	uint32_t tx_ng_count;
	uint32_t rx_count;

private:
	bool waitConfigResponse();

	bool in_operation_;
	bool is_sending_;
	int8_t response_len_;
	int8_t receiving_len_;

	int16_t read4Hex();
};



#endif /* INC_ES920LR_HPP_ */
