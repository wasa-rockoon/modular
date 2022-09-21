/*
 * shared.cpp
 *
 *  Created on: Sep 17, 2022
 *      Author: yuuki.fj
 */

#include "shared.hpp"

//template <typename T, uint32_t TIMEOUT>
//T Shared<T, TIMEOUT>::set(const T& value) {
//	value_ = value;
//	last_update_ = HAL_GetTick();
//	has_value_ = true;
//	return value;
//}

//template <typename T, uint32_t TIMEOUT>
//T Shared<T, TIMEOUT>::set(const T& value) {
//	value_ = value;
//	last_update_ = HAL_GetTick();
//	has_value_ = true;
//}

//template <typename T, uint32_t TIMEOUT>
//bool Shared<T, TIMEOUT>::set(uint8_t type, const Command& command) {
//	union Payload p;
//	if (command.get(type, 0, p)) {
//		set(p.as<T>());
//		return  true;
//	}
//	return false;
//}
//
//template <typename T, uint32_t TIMEOUT>
//bool Shared<T, TIMEOUT>::setIf(uint8_t type, const Command& command, T value) {
//	if (command.get(type, 0)) {
//		set(value);
//		return true;
//	}
//	return false;
//}


//template <uint32_t TIMEOUT>
//inline Shared<uint32_t, TIMEOUT>::operator T() const {
//	return value_;
//}
//
//template <uint32_t TIMEOUT>
//inline Shared<float, TIMEOUT>::operator float() const {
//	return value_;
//}
//
//template <uint32_t TIMEOUT>
//inline Shared<float, TIMEOUT>::operator float() const {
//	return value_;
//}
