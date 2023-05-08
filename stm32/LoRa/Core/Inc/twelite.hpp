/*
 * twelite.hpp
 *
 *  Created on: Feb 24, 2023
 *      Author: yuuki.fj
 */

#ifndef INC_TWELITE_HPP_
#define INC_TWELITE_HPP_

#define TWE_BUF_SIZE 64


#include "uart.hpp"
#include "command.hpp"

class TWELITE: public UART {
public:
	TWELITE(UART_HandleTypeDef& huart);

	bool begin(bool reset = true);
	bool interactiveMode();
	bool config(uint8_t command, const char parameter[]);
	bool saveConfig();

	void send(const Command& message);
	void send();

	bool update(Command& message);

	inline void setDestination(uint8_t id) { dest_id_ = id; };

	inline int getLQI() const { return lqi_; }
	inline int getReceivedCount() const { return received_count_; }
	inline int getSentCount() const { return sent_count_; }
	inline int getErrorCount() const { return error_count_ + dropped_count_; }

private:

	BinaryChannel channel_;

	uint8_t dest_id_;

	uint8_t rx_buf_[TWE_BUF_SIZE];
	unsigned rx_count_;

	int lqi_;

	unsigned sent_count_;
	unsigned received_count_;
	unsigned dropped_count_;
	unsigned error_count_;

	bool receive();

	inline void error() { error_count_++; }

};


#endif /* INC_TWELITE_HPP_ */
