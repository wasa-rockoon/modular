#include "Arduino.h"
#include <CANBus.hpp>

#include <CAN.h>
#include <EEPROM.h>

#define CAN_BAUD 1000000
#define CAN_RX_PIN 32
#define CAN_TX_PIN 33

unsigned getMillis() {
  return millis();
}

void enableInterrupts() {
  
}

void disableInterrupts() {
  
}


uint8_t EEPROMemu;

uint8_t readEEPROM(unsigned addr) { return EEPROM.read(addr); }
void writeEEPROM(unsigned addr, uint8_t value) {
  EEPROM.write(addr, value);
  EEPROM.commit();
}
unsigned getUnique() { return ESP.getEfuseMac(); }

bool CANInit() {
  CAN.setPins(CAN_RX_PIN, CAN_TX_PIN);
  CAN.begin(CAN_BAUD);

  volatile uint32_t* pREG_IER = (volatile uint32_t*)0x3ff6b010;
  *pREG_IER &= ~(uint8_t)0x10;

  return true;
}

bool CANSend(uint32_t ext_id, uint8_t *buf, unsigned len) {
  CAN.beginExtendedPacket(ext_id);
  CAN.write(buf, len);
  CAN.endPacket();
  return true;
}

bool CANSetFilter(uint32_t id, uint32_t mask) {
  // Serial.printf("filter %x %x\n", id, mask);
  // CAN.filterExtended(id, mask);

  return true;
}