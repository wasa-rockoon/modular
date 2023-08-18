/*
 * E220.hpp
 *
 *  Created on: Jul 10, 2023
 *      Author: yuuki.fj
 */

#ifndef INC_E220_HPP_
#define INC_E220_HPP_


#include "uart.hpp"

#define E220_BROADCAST 0xFFFF

#ifndef E220_TIMEOUT_MS
#define E220_TIMEOUT_MS 100
#endif

#define E220_PARAM_MAX 8

class E220: public UART {
public:

  enum class Mode : uint8_t {
    NORMAL = 0b00,
    WOR_TX = 0b01,
    WOR_RX = 0b10,
    CONFIG_DS = 0b11,
  };

  enum class ADDR : uint8_t {
    ADDH = 0x00,
    ADDL = 0x01,
    REG0 = 0x02,
    REG1 = 0x03,
    REG2 = 0x04,
    REG3 = 0x05,
    CRYPT_H = 0x06,
    CRYPT_L = 0x07,
    VERSION = 0x08,
  };

  enum class SF : uint8_t {
    SF5 = 0b000,
    SF6 = 0b001,
    SF7 = 0b010,
    SF8 = 0b011,
    SF9 = 0b100,
    SF10 = 0b101,
    SF11 = 0b110,
  };

  enum class BW : uint8_t {
    BW125kHz = 0b00,
    BW250kHz = 0b01,
    BW500kHz = 0x10,
  };

  enum class Power : uint8_t {
    POWER13dBm = 0b01,
    POWER7dBm = 0b10,
    POWER0dBm = 0b11,
  };

  enum class SendMode : uint8_t {
    TRANSPARENT = 0b0,
    FIXED = 0b1,
  };

  E220(UART_HandleTypeDef& huart, uint8_t* buf,
      unsigned ring_size, unsigned tail_size,
      GPIO_TypeDef* AUX_GPIOx, uint16_t AUX_GPIO_Pin,
      GPIO_TypeDef* M0_GPIOx, uint16_t M0_GPIO_Pin,
      GPIO_TypeDef* M1_GPIOx, uint16_t M1_GPIO_Pin
      );

  bool begin();
  bool setMode(Mode mode);

  bool isBusy();

  bool sendTransparent(const uint8_t* data, unsigned len);
  bool send(uint16_t addr, uint8_t channel, const uint8_t* data, unsigned len);

  unsigned receive(uint8_t*& data);

  bool setModuleAddr(uint16_t addr);
  bool setSerialBaudRate(unsigned baud);
  bool setDataRate(SF sf, BW bw);
  bool setEnvRSSIEnable(bool enable);
  bool setPower(Power power);
  bool setChannel(uint8_t channel);
  bool setRSSIEnable(bool enable);
  bool setSendMode(SendMode mode);

  inline uint8_t getRSSI() const { return rssi_; };
  uint8_t getEnvRSSI();

  bool writeRegister(ADDR addr, const uint8_t* parameters, uint8_t len = 1);
  bool writeRegisterWithMask(ADDR addr, uint8_t value, uint8_t mask);
  bool readRegister(ADDR addr, uint8_t* parameters, uint8_t len = 1);

private:
  GPIO_TypeDef* AUX_GPIOx_;
  GPIO_TypeDef* M0_GPIOx_;
  GPIO_TypeDef* M1_GPIOx_;
  uint16_t AUX_GPIO_Pin_;
  uint16_t M0_GPIO_Pin_;
  uint16_t M1_GPIO_Pin_;

  bool RSSI_enabled_;
  unsigned baud_;
  uint8_t rssi_;
};


#endif /* INC_E220_HPP_ */
