/*
 * shared.hpp
 *
 *  Created on: Sep 17, 2022
 *      Author: yuuki.fj
 */

#ifndef SHARED_HPP_
#define SHARED_HPP_

#include <stdint.h>
#include "command.hpp"
#include "main.h"

//extern uint32_t HAL_GetTick(void);

template <typename T, uint32_t TIMEOUT = 1000>
class Shared {
public:
	Shared(): last_update_(0), has_value_(false) {}
	Shared(T value): value_(value), last_update_(0), has_value_(true) { }

	T set(const T& value) {
		value_ = value;
		last_update_ = HAL_GetTick();
		has_value_ = true;
		return value;
	}
	inline T get() const { return value_; }

	inline bool hasValue() const { return has_value_; };
	inline bool isValid() const { return has_value_ && age() < TIMEOUT; }
	inline uint32_t age() const { return HAL_GetTick() - last_update_; }
	inline T operator=(const T value) { return set(value); }

	inline operator T() const { return value_; }

	bool set(uint8_t type, Command &command) {
		union Payload p;
		if (command.get(type, 0, p)) {
			set(payloadAs<T>(p));
			return true;
		}
		return false;
	}

	bool setIf(uint8_t type, Command &command, T value) {
		if (command.get(type, 0)) {
			set(value);
			return true;
		}
		return false;
	}

//	inline operator float() const;
//	inline operator uint32_t() const;
//	inline operator int32_t() const;

private:
	T value_;
	uint32_t last_update_;
	bool has_value_;
};


#endif /* SHARED_HPP_ */
