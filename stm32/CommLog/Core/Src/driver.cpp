#include "CANBus.hpp"
#include "main.h"
#include "app.h"

#define CAN_TIMEOUT_MS 10


unsigned getMillis() {
  return HAL_GetTick();
}

uint8_t EEPROMemu;

uint8_t readEEPROM(unsigned addr) { return EEPROMemu; }
void writeEEPROM(unsigned addr, uint8_t value) { EEPROMemu = value; }

unsigned getUnique() { return HAL_GetUIDw0(); }


CAN_TxHeaderTypeDef CanTxHeader;
CAN_RxHeaderTypeDef CanRxHeader;
uint32_t CanTxMailbox;

bool CANInit() {
  if (HAL_CAN_Start(&hcan) != HAL_OK) {
    Error_Handler();
  }

  if (HAL_CAN_ActivateNotification
      (&hcan, CAN_IT_RX_FIFO0_MSG_PENDING | CAN_IT_RX_FIFO1_MSG_PENDING)
      != HAL_OK) {
    Error_Handler();
  }
  CanTxHeader.RTR = CAN_RTR_DATA;
  CanTxHeader.IDE = CAN_ID_EXT;
  CanTxHeader.TransmitGlobalTime = DISABLE;
  return true;
}

bool CANSend(uint32_t ext_id, uint8_t *buf, unsigned len) {
  CanTxHeader.ExtId = ext_id;
  CanTxHeader.DLC = len;

  unsigned start = HAL_GetTick();
  while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan) == 0) {
    if (HAL_GetTick() - start > CAN_TIMEOUT_MS) return false;
  }

  if (HAL_CAN_AddTxMessage(&hcan, &CanTxHeader, buf, &CanTxMailbox) != HAL_OK) {
    Error_Handler();
  }
  return true;
}

bool CANSetFilter(uint32_t id, uint32_t mask) {
  uint32_t fId = id << 3 | 0b100;
  uint32_t fMask = mask << 3 | 0b1100;

  CAN_FilterTypeDef filter0;
  filter0.FilterIdHigh = fId >> 16;
  filter0.FilterIdLow = fId;
  filter0.FilterMaskIdHigh = fMask >> 16;
  filter0.FilterMaskIdLow = fMask;
  filter0.FilterScale = CAN_FILTERSCALE_32BIT;
  filter0.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  filter0.FilterBank = 0;
  filter0.FilterMode = CAN_FILTERMODE_IDMASK;
  filter0.FilterActivation = ENABLE;
  if (HAL_CAN_ConfigFilter(&hcan, &filter0) != HAL_OK) {
    Error_Handler();
  }

  CAN_FilterTypeDef filter1;
  filter1.FilterIdHigh = fId >> 16;
  filter1.FilterIdLow = fId | 0b1000;
  filter1.FilterMaskIdHigh = fMask >> 16;
  filter1.FilterMaskIdLow = fMask;
  filter1.FilterScale = CAN_FILTERSCALE_32BIT;
  filter1.FilterFIFOAssignment = CAN_FILTER_FIFO1;
  filter1.FilterBank = 2;
  filter1.FilterMode = CAN_FILTERMODE_IDMASK;
  filter1.FilterActivation = ENABLE;
  if (HAL_CAN_ConfigFilter(&hcan, &filter1) != HAL_OK) {
    Error_Handler();
  }

  return true;
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
  uint8_t data[8];
  if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &CanRxHeader, data) !=
      HAL_OK) {
    Error_Handler();
  }

  CANReceived(CanRxHeader.ExtId, data, CanRxHeader.DLC);
}
void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan) {
  uint8_t data[8];
  if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO1, &CanRxHeader, data) !=
      HAL_OK) {
    Error_Handler();
  }

  CANReceived(CanRxHeader.ExtId, data, CanRxHeader.DLC);
}

