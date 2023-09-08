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


class TWELITE: public UART {
public:
	TWELITE(UART_HandleTypeDef& huart, uint8_t* buf,
      unsigned ring_size, unsigned tail_size);

	bool begin(bool reset = true);
	bool interactiveMode();
	bool config(uint8_t command, const char parameter[]);
	bool saveConfig();

	bool send(const uint8_t* data, unsigned len);
  unsigned receive(uint8_t*& data);

	inline void setDestination(uint8_t id) { dest_id_ = id; };

	inline int getLQI() const { return lqi_; }
	inline int getReceivedCount() const { return received_count_; }
	inline int getSentCount() const { return sent_count_; }
	inline int getErrorCount() const { return error_count_ + dropped_count_; }

private:
	uint8_t dest_id_;

	int lqi_;

	unsigned sent_count_;
	unsigned received_count_;
	unsigned dropped_count_;
	unsigned error_count_;

	inline void error() { error_count_++; }

};


#endif /* INC_TWELITE_HPP_ */
