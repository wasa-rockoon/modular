/*
 * diagnostics.cpp
 *
 *  Created on: Sep 15, 2022
 *      Author: yuuki.fj
 */

#include "diagnostics.hpp"
#include <stdio.h>


Diagnostics::Diagnostics(module_id my_id) {
	module_id_ = my_id;
	for (int n = 0; n < MAX_MODULES; n++) {
		if ((0b1 << n) & my_id) {
			module_id_n_ = n;
			break;
		}
	}

	modules_ = 0b00111111 & ~((uint8_t)0b1 << module_id_n_);

	status_ = 0x00ffffff;
	setStatus(STATUS_ALL, STATUS_OK);
}

status Diagnostics::getStatus(module_id mid, status_id sid) {
	for (int n = 0; n < MAX_MODULES; n++) {
		if ((0b1 << n) & mid) {
			if (status_ & (sid << (n * STATUS_SIZE)))
				return STATUS_NG;
		}
	}
	return STATUS_OK;
}

void Diagnostics::setStatus(status_id sid, status s) {
	uint8_t status_pos = module_id_n_ * STATUS_SIZE;
	status_ = status_ & ~((uint32_t)sid << status_pos);
	if (s == STATUS_NG) {
		status_ = status_ | (uint32_t)(sid & STATUS_ALL) << status_pos;
	}
}


void Diagnostics::update(uint32_t tick) {
	for (int n = 0; n < MAX_MODULES; n++) {
		if (n == module_id_n_) continue;
		if ((tick - last_received_[n]) > DIAG_TIMEOUT_TICK) {
			modules_ = modules_ | 0b1 << n;
		}
		else {
			modules_ = modules_ & ~((uint8_t)0b1 << n);
		}
	}
}

void Diagnostics::update(module_id from, uint32_t raw, uint32_t tick) {
	for (int n = 0; n < MAX_MODULES; n++) {
		if ((0b1 << n) & from) {
			last_received_[n] = tick;
			modules_ = modules_ & ~((uint8_t)0b1 << n);

			uint8_t status_pos = n * STATUS_SIZE;
			status_ = status_ & ~((uint32_t)STATUS_ALL << status_pos);
			status_ = status_ | (raw & ((uint32_t)STATUS_ALL << status_pos));
		}
	}
}

void Diagnostics::printSummary() {
	const char names[] = {'B', 'C', 'S', 'G', 'N', 'I'};
	for (int n = 0; n < MAX_MODULES; n++) {
		module_id mid = 0b1 << n;
		printf("%c: %d %d%d%d%d\n",
				names[n],
				!isAlive(mid),
				getStatus(mid, STATUS_3),
				getStatus(mid, STATUS_2),
				getStatus(mid, STATUS_1),
				getStatus(mid, STATUS_0)
		);
	}
}

