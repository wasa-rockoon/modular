/*
 * indicator.hpp
 *
 *  Created on: Aug 26, 2023
 *      Author: yuuki.fj
 */

#ifndef INDICATOR_HPP_
#define INDICATOR_HPP_

#include "stdint.h"

#define INDICATOR_PWM_PERIOD 16

extern "C" uint32_t HAL_GetTick(void);

class Indicator {
public:
  bool update();

  inline void blink(unsigned sustain_ms = 50) {
    if (blink_until_ms_ < HAL_GetTick() + sustain_ms)
      blink_until_ms_ = HAL_GetTick() + sustain_ms;
  }
  void watchCount(unsigned count, unsigned blink_sustain_ms = 50);

  inline void set(uint8_t duty) { duty_ = duty; }
  inline void reset() { duty_ = 0; }

private:
  unsigned blink_until_ms_;
  uint8_t duty_;
};


#endif /* INDICATOR_HPP_ */
