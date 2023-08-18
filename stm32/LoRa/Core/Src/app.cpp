/*
 * app.cpp
 *
 *  Created on: Aug 2, 2023
 *      Author: yuuki.fj
 */


#include "app.h"

#include "Packet.hpp"
#include "CANBus.hpp"
#include "Shared.hpp"
#include "E220.hpp"


CANBus bus(SYSTEM, NODE);

uint8_t lora1_buf[LORA_BUF_SIZE + LORA_PACKET_SIZE_MAX];
E220 lora1(huart1, lora1_buf, LORA_BUF_SIZE, LORA_PACKET_SIZE_MAX,
    LORA1_AUX_GPIO_Port, LORA1_AUX_Pin, LORA1_M0_GPIO_Port, LORA1_M0_Pin,
    LORA1_M1_GPIO_Port, LORA1_M1_Pin);

uint8_t lora2_buf[LORA_BUF_SIZE + LORA_PACKET_SIZE_MAX];
E220 lora2(huart2, lora2_buf, LORA_BUF_SIZE, LORA_PACKET_SIZE_MAX,
    LORA2_AUX_GPIO_Port, LORA2_AUX_Pin, LORA2_M0_GPIO_Port, LORA2_M0_Pin,
    LORA2_M1_GPIO_Port, LORA2_M1_Pin);


#if SYSTEM == LAUNCHER

// LoRa 1 : LAUCHER -> GS      (telemetry)
// LoRa 2 : Rocket  -> LAUCHER (telemetry relay)

#define LORA1_CHANNEL LAUNCHER_TLM_CHANNEL
#define LORA2_CHANNEL ROCKET_TLM_CHANNEL

Shared<float16> battery_V('B', 'P');
Shared<int32_t> longitude('L', 'O');
Shared<int32_t> latitude('L', 'A');
Shared<float> gps_altitude('L', 'H');
Shared<float> pressure_altitude('P', 'H');
Shared<uint8_t> command_RSSI('C', 'R');

uint8_t rocket_RSSI  = 255;
uint8_t env_RSSI     = 255;

uint8_t launcher_seq = 0;

uint8_t relay_buf[LORA_PACKET_SIZE_MAX];
Packet relay_packet(relay_buf, sizeof(relay_buf));
bool relay_needed = false;

unsigned packet_round = 0;



#elif SYSTEM == GS1 || SYSTEM == GS2

// LoRa 1 : LAUCHER -> GS (telemetry)
// LoRa 2 : Rocket  -> GS (telemetry)

#define LORA1_CHANNEL LAUNCHER_TLM_CHANNEL
#define LORA2_CHANNEL ROCKET_TLM_CHANNEL


#endif

unsigned long blink_ms[3];

void setLED(unsigned led, bool set) {
  switch (led) {
  case 0:
    HAL_GPIO_WritePin(LED_ERROR_GPIO_Port, LED_ERROR_Pin, set ? GPIO_PIN_RESET : GPIO_PIN_SET);
    break;
  case 1:
    HAL_GPIO_WritePin(LED_STATUS1_GPIO_Port, LED_STATUS1_Pin, set ? GPIO_PIN_RESET : GPIO_PIN_SET);
    break;
  case 2:
    HAL_GPIO_WritePin(LED_STATUS2_GPIO_Port, LED_STATUS2_Pin, set ? GPIO_PIN_RESET : GPIO_PIN_SET);
    break;
  }
}

void blink(unsigned led) {
  blink_ms[led] = HAL_GetTick();
  setLED(led, true);
}

bool LoRa1_setup() {
  bool ok = true;
  ok &= lora1.setMode(E220::Mode::CONFIG_DS);
  ok &= lora1.setSerialBaudRate(38400);
  ok &= lora1.setDataRate(E220::SF::SF9, E220::BW::BW125kHz);
  ok &= lora1.setEnvRSSIEnable(true);
  ok &= lora1.setChannel(LORA1_CHANNEL);
  ok &= lora1.setRSSIEnable(true);
  ok &= lora1.setMode(E220::Mode::NORMAL);
  return ok;
}
bool LoRa2_setup() {
  bool ok = true;
  ok &= lora2.setMode(E220::Mode::CONFIG_DS);
//  ok &= lora2.setModuleAddr(ROCKOON_ADDR);
  ok &= lora2.setSerialBaudRate(38400);
  ok &= lora2.setDataRate(E220::SF::SF9, E220::BW::BW125kHz);
  ok &= lora2.setEnvRSSIEnable(true);
  ok &= lora2.setChannel(LORA2_CHANNEL);
  ok &= lora2.setRSSIEnable(true);
  ok &= lora2.setMode(E220::Mode::NORMAL);
  return ok;
}


extern void setup() {

#ifdef DEBUG
  printf("Start\n");
#endif

  setLED(0, true);
  setLED(1, false);
  setLED(2, false);

  bool ok = true;
  ok &= bus.begin();
  ok &= lora1.begin();
  ok &= lora2.begin();

#ifndef DEBUG
    HAL_IWDG_Refresh(&hiwdg);
#endif

  ok &= LoRa1_setup();
  ok &= LoRa2_setup();

#ifndef DEBUG
    HAL_IWDG_Refresh(&hiwdg);
#endif

#ifdef DEBUG
  printf("ok: %d\n", ok);
#endif

  bus.listenAll();

#if SYSTEM == LAUNCHER
  bus.subscribe(battery_V, 1000);
  bus.subscribe(longitude, 10000);
  bus.subscribe(latitude, 10000);
  bus.subscribe(gps_altitude, 10000);
  bus.subscribe(pressure_altitude, 1000);
  bus.subscribe(command_RSSI, 10000);
#endif

  if (ok) setLED(0, false);

  HAL_TIM_Base_Start_IT(&htim14);
}

extern void loop() {
  bus.update();

  Packet packet = bus.receive();

  if (packet.isValid()) {

#if SYSTEM == LAUNCHER

#endif


#ifdef DEBUG
    packet.print();
#endif
  }

#if SYSTEM == LAUNCHER

//  int16_t c = lora1.read();
//  if (c >= 0) printf("[%d] \n", c);

  uint8_t* rx;
  unsigned len = lora2.receive(rx);

  if (len > 0) {
    lora2.clear();
    rocket_RSSI = lora2.getRSSI();

    Packet rocket(rx, len, len);
#ifdef DEBUG
    rocket.print();
#endif

    rocket.copyTo(relay_packet);
    relay_needed = true;

    bus.send(relay_packet);

    blink(2);
  }


#elif SYSTEM == GS1 || SYSTEM == GS2

  uint8_t received_buf[LORA_PACKET_SIZE_MAX];
  Packet received_packet(received_buf, sizeof(received_buf));


  uint8_t* rx;
  unsigned len = lora1.receive(rx);

  if (len > 0) {
    lora1.clear();

//        printf("%d %x %x %x %x %x %x %x %x\n",
//            len, rx[0], rx[1], rx[2], rx[3], rx[4], rx[5], rx[6], rx[7]);
//

    Packet launcher(rx, len, len);

    launcher.copyTo(received_packet);
    received_packet.end().append('r', lora1.getRSSI());

#ifdef DEBUG
    received_packet.print();
#endif

//    printf("%d %d %d %d %d %d\n", launcher.size(), received_packet.size(), launcher.begin().ptr_, launcher.end_.ptr_,received_packet.begin().ptr_, received_packet.end_.ptr_ );

    bus.send(received_packet);

    blink(1);
  }

  len = lora2.receive(rx);

  if (len > 0) {
    lora2.clear();

    Packet rocket(rx, len, len);

    rocket.copyTo(received_packet);
    received_packet.end().append('r', lora2.getRSSI());

#ifdef DEBUG
    received_packet.print();
#endif

    bus.send(received_packet);

    blink(2);
  }

#endif

  for (unsigned led = 0; led < 3; led++) {
    if (HAL_GetTick() - blink_ms[led] > BLINK_MS) setLED(led, false);
  }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim == &htim14) {

#if SYSTEM == LAUNCHER

    switch (packet_round) {
    case 1:
      if (relay_needed) {
        lora1.sendTransparent(relay_packet.buf, relay_packet.len);
        relay_needed = false;
        break;
      }
      else packet_round = 0;
    case 0:
      env_RSSI = lora1.getEnvRSSI();

      uint8_t buf[LORA_PACKET_SIZE_MAX];
      Packet launcher(buf, sizeof(buf));
      launcher.set(TELEMETRY, 'T', SYSTEM, BROADCAST);
      launcher.set_(NODE, launcher_seq++);
      battery_V.appendIfValid(launcher, 'B');
      latitude.appendIfValid(launcher, 'A');
      longitude.appendIfValid(launcher, 'O');
      gps_altitude.appendIfValid(launcher, 'H');
      pressure_altitude.appendIfValid(launcher, 'h');
      command_RSSI.appendIfValid(launcher, 'c');
      launcher.end()
        .append('c', command_RSSI)
        .append('r', rocket_RSSI)
        .append('e', env_RSSI);
//      printf("+ ");
//      uint8_t* rx = launcher.buf;
#ifdef DEBUG
//       printf("%d %x %x %x %x %x %x %x %x\n",
//          launcher.len, rx[0], rx[1], rx[2], rx[3], rx[4], rx[5], rx[6], rx[7]);
//      launcher.print();
#endif
      lora1.sendTransparent(launcher.buf, launcher.len);
      break;
    }
    packet_round++;
    if (packet_round > 1) packet_round = 0;

    blink(1);

#endif
  }
}
