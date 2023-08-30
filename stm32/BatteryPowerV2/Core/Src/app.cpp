/*
 * Battery Power Module V2
 * app.cpp
 *
 *  Created on: Aug 24, 2023
 *      Author: yuuki.fj
 */

#include "app.h"


#include <CANBus.hpp>
#include <Packet.hpp>
#include <Shared.hpp>
#include <indicator.hpp>


CANBus bus(NODE);
Indicator error_indicator;
Indicator status_indicator;

uint16_t adc_values[9];

float temperature;
float vdd_V;
float vdd_I;
float vcc_V;
float vcc_I;
float bat2_V;
float bat1_V;
float vpp_V;

enum class Sequence: uint8_t {
  NO_LAUNCH,
  WAITING,
  STABILIZING,
  IGNITING,
  COMPLETED,
};

Shared<Sequence> launch_sequence(Sequence::NO_LAUNCH);

extern void setup() {
#ifdef DEBUG
  printf("start\n");
#endif
  HAL_GPIO_WritePin(LED_ERROR_GPIO_Port, LED_ERROR_Pin, GPIO_PIN_RESET);

  bus.begin();
  bus.subscribe(launch_sequence, TELEMETRY, 'I', 's');

  HAL_Delay(100);

  HAL_ADCEx_Calibration_Start(&hadc);
  HAL_ADC_Start_DMA(&hadc, (uint32_t*)adc_values, 9);

  HAL_TIM_Base_Start_IT(&htim2);
  HAL_TIM_Base_Start_IT(&htim14);

  HAL_GPIO_WritePin(LED_ERROR_GPIO_Port, LED_ERROR_Pin, GPIO_PIN_SET);
}

extern void loop() {
  bus.update();

  error_indicator.watchCount(bus.getErrorCount());
  error_indicator.set(bus.insanity());
  HAL_GPIO_WritePin(LED_ERROR_GPIO_Port, LED_ERROR_Pin, (GPIO_PinState)!error_indicator.update());
  HAL_GPIO_WritePin(LED_STATUS_GPIO_Port, LED_STATUS_Pin, (GPIO_PinState)!status_indicator.update());

#ifdef DEBUG
  if (HAL_GetTick() % 1000 == 0) {
    bus.printErrorSummary();
    bus.printSanitySummary();
  }
#endif
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim == &htim2) {
    float voltages[8];
    for (int i = 0; i < 8; i++) {
      voltages[i] = (float)adc_values[i] * 3.3 / 4095;
    }

//    float temp    = voltages[0]
    float vdd_V_  = voltages[1] * 3.3 / 1.245;
    float vdd_I_  = voltages[2] / 100 / 0.033;
    float vcc_V_  = voltages[3] * 5.0 / 1.245;
    float vcc_I_  = voltages[4] / 100 / 0.033;
    float bat2_V_ = voltages[5] * 11;
    float bat1_V_ = voltages[6] * 11;
    float vpp_V_  = voltages[7] * 11;

    vdd_V  = vdd_V_  * (1 - VOLTAGE_FILTER_A) + vdd_V  * VOLTAGE_FILTER_A;
    vdd_I  = vdd_I_  * (1 - CURRENT_FILTER_A) + vdd_I  * CURRENT_FILTER_A;
    vcc_V  = vcc_V_  * (1 - VOLTAGE_FILTER_A) + vcc_V  * VOLTAGE_FILTER_A;
    vcc_I  = vcc_I_  * (1 - CURRENT_FILTER_A) + vcc_I  * CURRENT_FILTER_A;
    bat2_V = bat2_V_ * (1 - VOLTAGE_FILTER_A) + bat2_V * VOLTAGE_FILTER_A;
    bat1_V = bat1_V_ * (1 - VOLTAGE_FILTER_A) + bat1_V * VOLTAGE_FILTER_A;
    vpp_V  = vpp_V_  * (1 - VOLTAGE_FILTER_A) + vpp_V  * VOLTAGE_FILTER_A;
  }
  else if (htim == &htim14) {

    bool supply_connected = HAL_GPIO_ReadPin(SUPPLY_CON_GPIO_Port, SUPPLY_CON_Pin);
    bool supply = supply_connected && (launch_sequence.value() < Sequence::WAITING);
    supply = true;
#ifdef ENABLE_SUPPLY
    HAL_GPIO_WritePin(SUPPLY_5V_GPIO_Port, SUPPLY_5V_Pin, (GPIO_PinState)supply);
#endif

    uint8_t buf[BUF_SIZE(9)];
    Packet battery(buf, sizeof(buf));
    battery.set(TELEMETRY, 'B', BROADCAST);
    battery.begin()
      .append('P', int16_t(vpp_V  * 1000))
      .append('B', int16_t(bat1_V * 1000))
      .append('b', int16_t(bat2_V * 1000))
      .append('C', int16_t(vcc_V  * 1000))
      .append('D', int16_t(vdd_V  * 1000))
      .append('c', int16_t(vcc_I  * 1000))
      .append('d', int16_t(vdd_I  * 1000))
#ifdef ENABLE_SUPPLY
      .append('U', supply_connected)
      .append('S', supply)
#endif
      ;
    bus.send(battery);

    bus.sanity(1, true);
    bus.sanity(2, VPP_V_MIN < vpp_V);
    bus.sanity(3, BAT1_V_MIN < bat1_V && bat1_V < BAT_V_MAX);
    bus.sanity(4, BAT2_V_MIN < bat2_V && bat2_V < BAT_V_MAX);
    bus.sanity(5, std::abs(vcc_V - 5.0) < VCC_V_ERROR);
    bus.sanity(6, std::abs(vdd_V - 3.3) < VDD_V_ERROR);
    bus.sanity(7, vcc_I < VCC_I_MAX);
    bus.sanity(8, vdd_I < VDD_I_MAX);

    status_indicator.blink(10);
  }
}
