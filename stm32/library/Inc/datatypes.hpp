/*
 * datatypes.hpp
 *
 *  Created on: Aug 30, 2023
 *      Author: yuuki.fj
 */

#ifndef DATATYPES_HPP_
#define DATATYPES_HPP_


enum class Sequence: unsigned {
  NO_LAUNCH,
  WAITING,
  STABILIZING,
  IGNITING,
  COMPLETED,
};

struct Launch {
  bool igniter: 1;
  bool condition: 1;
  bool allowed: 1;
  bool connected: 1;
  bool supplying: 1;
  Sequence sequence: 3;
};

struct Supply {
  bool connected: 1;
  bool supplying: 1;
};

#endif /* DATATYPES_HPP_ */
