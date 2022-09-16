/*
 * diagnostics.hpp
 *
 *  Created on: Sep 15, 2022
 *      Author: yuuki.fj
 */

#ifndef DIAGNOSTICS_HPP_
#define DIAGNOSTICS_HPP_

#include <stdint.h>


#define DIAG_TIMEOUT_TICK 5000

#define MAX_MODULES 6
#define STATUS_SIZE 4

typedef bool status;

#define STATUS_OK 0
#define STATUS_NG 1

typedef uint8_t module_id;

#define MODULE_BATTERY_N 0
#define MODULE_COMMLOG_N 1
#define MODULE_SENSOR_N  2
#define MODULE_IGNITER_N 3
#define MODULE_NAV_N     4
#define MODULE_IMU_N     5

#define MODULE_BATTERY (0b1 << 0)
#define MODULE_COMMLOG (0b1 << 1)
#define MODULE_SENSOR  (0b1 << 2)
#define MODULE_IGNITER (0b1 << 3)
#define MODULE_NAV     (0b1 << 4)
#define MODULE_IMU     (0b1 << 5)

#define MODULE_ALL 0b00111111

typedef uint8_t status_id;

#define STATUS_0 (0b1 << 0)
#define STATUS_1 (0b1 << 1)
#define STATUS_2 (0b1 << 2)
#define STATUS_3 (0b1 << 3)

#define STATUS_ALL 0b1111

#define MODULE_N_TO_ID(n) ( 0b1 << (n) );

class Diagnostics {
public:

	Diagnostics(module_id my_id);

	inline bool isAlive(module_id mid) const { return !(mid & modules_); };
	status getStatus(module_id mid, status_id sid);
	void setStatus(status_id sid, status s);

	inline uint32_t encode() const { return (modules_ << 24) | status_; }
	void update(uint32_t tick);
	void update(module_id from, uint32_t raw, uint32_t tick);

	void printSummary();

private:
	module_id module_id_;
	uint8_t module_id_n_;
	uint8_t modules_;
	uint32_t status_;
	uint32_t last_received_[MAX_MODULES];
};



#endif /* DIAGNOSTICS_HPP_ */
