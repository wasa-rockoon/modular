/*
 * app.hpp
 *
 *  Created on: Aug 31, 2023
 *      Author: yuuki.fj
 */

#ifndef INC_APP_H_
#define INC_APP_H_


#include "main.h"

#define NODE 'U'


#ifdef __cplusplus
extern "C" {
#endif

extern CAN_HandleTypeDef hcan;

extern IWDG_HandleTypeDef hiwdg;

extern void setup();
extern void loop();

//extern void USBReceived(uint8_t* buf, uint8_t len);

#ifdef __cplusplus
};
#endif


#endif /* INC_APP_H_ */
