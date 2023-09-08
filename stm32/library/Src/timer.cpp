/*
 * timer.cpp
 *
 *  Created on: Sep 9, 2023
 *      Author: yuuki.fj
 */

#include "timer.hpp"

extern "C" uint32_t HAL_GetTick(void);

Timer::Timer(float freq) {
  last_exec_tick_ = 0;
  setFreq(freq);
}

bool Timer::exec() {
  bool exec = false;
  while (HAL_GetTick() - last_exec_tick_ >= period_tick_) {
    exec = true;
    last_exec_tick_ += period_tick_;
  }
  return exec;
}
