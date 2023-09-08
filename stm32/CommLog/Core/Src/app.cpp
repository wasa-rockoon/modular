/*
 * app.cpp
 *
 *  Created on: Jul 30, 2023
 *      Author: yuuki.fj
 */

#include "app.h"

#define NO_DETAIL_NODE_INFO
//#define CANBUS_BUFFER_SIZE 256

#include "fatfs.h"
#include <CANBus.hpp>
#include <Packet.hpp>
#include <indicator.hpp>
#include <timer.hpp>
#include "uart.hpp"
#include "es920lr.hpp"
#include "twelite.hpp"

CANBus bus(NODE);
Indicator status_indicator;
Timer tlm_timer(TLM_FREQ);
Timer sd_sync_timer(SD_SYNC_FREQ);


#ifdef TWELITE
uint8_t twelite_buf[TWELITE_BUF_SIZE + TWELITE_PACKET_SIZE_MAX];
TWELITE twelite(huart1, twelite_buf, TWELITE_BUF_SIZE, TWELITE_PACKET_SIZE_MAX);
bool twelite_ok = false;
#endif

#ifdef LORA
uint8_t lora_buf[LORA_BUF_SIZE + LORA_PACKET_SIZE_MAX];
ES920LR lora(huart2, lora_buf, LORA_BUF_SIZE, LORA_PACKET_SIZE_MAX);
#endif

FATFS fs;  // file system
FIL fil; // File
FILINFO fno;
FRESULT fresult;  // result
UINT br, bw;  // File read/write count


bool lora_ok = false;
bool twelite_ok = false;
bool file_opened = false;

unsigned wrote_count = 0;
unsigned dropped_count = 0;


void SD_Write(Packet& packet);
bool LoRa_Setup();
void TWE_Setup();
bool SD_Init();


extern void setup() {
#ifdef DEBUG
  printf("Start\n");
#endif

  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  file_opened = SD_Init();

  // Reset TWELITE
  HAL_GPIO_WritePin(TWE_NRST_GPIO_Port, TWE_NRST_Pin, GPIO_PIN_RESET);
//  HAL_GPIO_WritePin(LORA_NRST_GPIO_Port, LORA_NRST_Pin, GPIO_PIN_RESET);
  HAL_Delay(100);
  HAL_GPIO_WritePin(TWE_NRST_GPIO_Port, TWE_NRST_Pin, GPIO_PIN_SET);
//  HAL_GPIO_WritePin(LORA_NRST_GPIO_Port, LORA_NRST_Pin, GPIO_PIN_SET);

#ifdef LORA
#ifdef LORA_SETUP
  lora_ok = LoRa_Setup();
#else
  lora_ok = lora.begin(true);
#endif
  lora_ok &= lora.startOperation();
#endif

#ifdef TWELITE
  twelite.setDestination(TWE_DEST_ID);
  twelite_ok = twelite.begin();

#ifdef TWE_SETUP
  twelite_ok &= TWE_Setup();
#endif

#endif

  bus.begin();
  bus.listenAll();

  bus.sanity(1, file_opened);
  bus.sanity(2, lora_ok);
  bus.sanity(3, twelite_ok);


  if (file_opened && lora_ok) HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
}

extern void loop() {
  bus.update();


//  Packet& sanity = bus.getSanitySummary();
//  sanity.writeCRC();
//  SD_Write(sanity);


  Packet packet = bus.receive();

  if (packet.isValid()) {

    SD_Write(packet);
    status_indicator.blink(1);

#if UNIT == GS1 || UNIT == GS2

    if (packet.kind() == COMMAND) {

#ifdef DEBUG
      packet.print();
#endif

      packet.setFrom(UNIT);

      if (lora_ok) lora.send(PANID, DEST_ADDR, packet.buf, packet.len);

      SD_Write(packet);

      status_indicator.blink(500);
    }
#endif

#ifdef DEBUG
//  packet.print();
#endif
  }

#ifdef LORA
  int8_t response = lora.getResponse();
#endif

#if UNIT == LAUNCHER && defined LORA

  uint8_t* buf;
  unsigned len = lora.receive(buf);

  if (len > 0) {
    lora.clear();

    Packet command(buf, len, len);

#ifdef DEBUG
      command.print();
#endif

    bus.send(command);
    SD_Write(command);

    status_indicator.blink(500);
  }

#endif

  if (sd_sync_timer.exec()) {
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
    f_sync(&fil);
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
  }

  if (tlm_timer.exec()) {
#if UNIT == LAUNCHER
    uint8_t buf[BUF_SIZE(3)];
    Packet comm(buf, sizeof(buf));
    comm.set(TELEMETRY, 'C');
    comm.begin()
#ifdef LORA
      .append('R', (uint8_t)std::max(255, -lora.rssi))
      .append('C', lora.rx_count)
#endif
      .append('W', wrote_count);
//      .append('D', dropped_count);
    bus.send(comm);
    SD_Write(comm);

    Packet& sanity = bus.getSanitySummary();
    sanity.writeCRC();
    SD_Write(sanity);

    Packet& errors = bus.getErrorSummary();
    errors.writeCRC();
    SD_Write(errors);

    status_indicator.blink(10);
#endif
  }


  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, (GPIO_PinState)!status_indicator.update());
}


bool SD_Init() {
  fresult = f_mount(&fs, "/", 1);

  fresult = f_open(&fil, "lists.txt", FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
  uint32_t file_id = f_size(&fil);
  for (unsigned n = 0; n <= file_id; n++) f_putc('1', &fil);
  fresult = f_close(&fil);

  char file_name[16];
  sprintf(file_name, "log%05u.bin", (unsigned)file_id);

  /* Open file to write/ create a file if it doesn't exist */
  fresult = f_open(&fil, file_name, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);

  return fresult == FR_OK;
}

void SD_Write(Packet& packet) {
  packet.writeCRC();

  if (file_opened) {
    unsigned written;

    uint8_t buf[BUF_SIZE(ENTRIES_MAX) + 5];
    *((uint32_t*)buf) = HAL_GetTick();;
    buf[4] = packet.len;
    memcpy(buf + 5, packet.buf, packet.len);

    if (f_write(&fil, buf, 5 + packet.len, &written) == FR_OK) wrote_count++;
    else dropped_count++;
  }
}


bool LoRa_Setup() {

#ifdef LORA
  bool ok = lora.begin(true);

  ok &= lora.config('b', "3", 1); // Bandwidth
  ok &= lora.config('c', "12", 2); // Spreading factor
  ok &= lora.config('d', ES920_CHANNEL, 2); // channel
  ok &= lora.config('e', PANID, 4); // PAN ID
  ok &= lora.config('f', OWN_ID, 4); // Own ID
  ok &= lora.config('g', DEST_ADDR, 4); // Destination ID
  ok &= lora.config('n', "2", 1); // Transfer mode
  ok &= lora.config('o', "1", 1); // Receive ID
  ok &= lora.config('p', "1", 1); // RSSI
  ok &= lora.config('u', "13", 2); // Power
  ok &= lora.config('A', "2", 1); // Payload format
#ifdef LAUNCHER
  ok &= lora.config('a', "1", 1); // Node
  ok &= lora.config('l', "2", 1); // Ack
#endif
#ifdef GS
  ok &= lora.config('a', "2", 1); // Node
  ok &= lora.config('l', "1", 1); // Ack
#endif
  ok &= lora.config('w', "", 0); // save
  return ok;
#endif
}

void TWE_Setup() {
#ifdef TWELITE
  HAL_Delay(100);
  twelite.interactiveMode();
  throgh(); HAL_Delay(1); throgh();
  twelite.config('a', TWE_APP_ID);
  throgh(); HAL_Delay(1); throgh();
  twelite.config('i', TWE_DEV_ID);
  throgh(); HAL_Delay(1); throgh();
  twelite.config('c', TWE_CHANNEL);
  throgh(); HAL_Delay(1); throgh();
//  twelite.config('m', "B");
//  throgh(); HAL_Delay(1); throgh();
  twelite.saveConfig();
#endif
}
