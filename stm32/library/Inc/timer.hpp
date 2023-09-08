/*
 * task.hpp
 *
 *  Created on: Sep 9, 2023
 *      Author: yuuki.fj
 */

#ifndef TIMER_HPP_
#define TIMER_HPP_

#include "stdint.h"
#include <algorithm>

class Timer {
public:
  Timer(float freq);

  inline void setFreq(float freq) { period_tick_ = std::max((unsigned)(1000.0 / freq), (unsigned)1); };
  inline void setPeriod(unsigned period_ms) { period_tick_ = period_ms; }

  bool exec();

private:
  uint32_t last_exec_tick_;
  uint32_t period_tick_;
};


#endif /* TIMER_HPP_ */
