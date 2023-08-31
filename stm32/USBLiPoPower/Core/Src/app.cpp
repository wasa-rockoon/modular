/*
 * app.cpp
 *
 *  Created on: Aug 31, 2023
 *      Author: yuuki.fj
 */

#include "app.h"

#include "CANBus.hpp"
#include "COBS.hpp"
#include "usbd_cdc_if.h"


CANBus bus(NODE);

uint8_t encoded[BUF_SIZE(ENTRIES_MAX) + 1];

extern void setup() {
#ifdef DEBUG
  printf("Start\n");
#endif
  bus.begin();
  bus.listenAll();
}

extern void loop() {
  bus.update();


  Packet packet = bus.receive();

  if (packet.isValid()) {
    unsigned encoded_len = COBS::encode(packet.buf, packet.len, encoded);
    encoded[encoded_len] = 0;
    CDC_Transmit_FS(encoded, encoded_len + 1);
  }


#ifdef DEBUG
  if (HAL_GetTick() % 1000 == 0) {
    bus.printErrorSummary();
    bus.printSanitySummary();
  }
#endif
}
