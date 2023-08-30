/*
 * indicator.cpp
 *
 *  Created on: Aug 26, 2023
 *      Author: yuuki.fj
 */

#include "indicator.hpp"


bool Indicator::update() {
  if (HAL_GetTick() < blink_until_ms_) return true;
  else return HAL_GetTick() % INDICATOR_PWM_PERIOD < duty_;
}

void Indicator::watchCount(unsigned count, unsigned blink_sustain_ms) {
  static unsigned count_prev = 0;
  if (count != count_prev) blink(blink_sustain_ms);
  count_prev = count;
}
