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
	ES920LR(UART_HandleTypeDef& huart);

	bool begin();
	bool config(uint8_t command, const uint8_t parameter[], uint8_t len);
	bool startOperation();
	void update();

	inline bool inOperation() { return in_operation_; }

private:
	bool waitConfigResponse();

	bool in_operation_;
};



#endif /* INC_ES920LR_HPP_ */
