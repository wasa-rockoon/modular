/*
 * Battery Power Module V2
 * app.h
 *
 *  Created on: Aug 24, 2023
 *      Author: yuuki.fj
 */

#ifndef INC_APP_H_
#define INC_APP_H_

#include "main.h"

#define NODE 'B'

#define ENABLE_SUPPLY

//#define ENABLE_HEATER

#define VOLTAGE_FILTER_A 0.95
#define CURRENT_FILTER_A 0.95

#define BLINK_MS 10


// Sanity conditions
#define VPP_V_MIN 8.0
#define BAT1_V_MIN 11.1
#define BAT2_V_MIN 8.0
#define BAT_V_MAX 14.0
#define VCC_V_ERROR 0.5
#define VDD_V_ERROR 0.2
#define VCC_I_MAX 0.5
#define VDD_I_MAX 0.5



#ifdef __cplusplus
extern "C" {
#endif

extern ADC_HandleTypeDef hadc;
extern DMA_HandleTypeDef hdma_adc;

extern CAN_HandleTypeDef hcan;

extern IWDG_HandleTypeDef hiwdg;

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim14;


extern void setup();
extern void loop();

#ifdef __cplusplus
};
#endif


#endif /* INC_APP_H_ */
