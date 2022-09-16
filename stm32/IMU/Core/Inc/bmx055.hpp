/*
 * bmx055.h
 *
 *  Created on: May 26, 2022
 *      Author: yuuki.fj
 */

#ifndef INC_BMX055_HPP_
#define INC_BMX055_HPP_

#include <stdint.h>
#include <stm32g4xx_hal.h>
#include <algebra.hpp>

enum AcclRange: uint8_t {
    PM2G = 2,
    PM4G = 4,
    PM8G = 8,
    PM16G = 16,
};

enum GyroRange: uint16_t {
    PM125DPS = 125,
    PM250DPS = 250,
    PM500DPS = 500,
    PM1000DPS = 1000,
    PM2000DPS = 2000,
};



class Function {
public:
	Function(SPI_HandleTypeDef& spi, GPIO_TypeDef* cs_port, uint16_t cs_pin);

    void start();
    void end();
    void writeRegister(uint8_t addr, uint8_t value);
    uint8_t readRegister(uint8_t addr);
    uint8_t readRegisters(uint8_t addr, uint8_t* data, uint8_t len);

    bool ok;

protected:
    SPI_HandleTypeDef& spi;
    GPIO_TypeDef* cs_port;
    uint16_t cs_pin;
};

class Accelerometer: public Function {
public:

	Accelerometer(SPI_HandleTypeDef& spi, GPIO_TypeDef* cs_port, uint16_t cs_pin);

    Vec3 read();
    void setRange(AcclRange range);

private:
    float factor;
};

class Gyroscope: public Function {
public:
	Gyroscope(SPI_HandleTypeDef& spi, GPIO_TypeDef* cs_port, uint16_t cs_pin);

    Vec3 read();
    void setRange(GyroRange range);

private:
    float factor;
};


class Magnetometer: public Function {
public:
	Magnetometer(SPI_HandleTypeDef& spi, GPIO_TypeDef* cs_port, uint16_t cs_pin);

    Vec3 center;
    float radius = 10;

    Vec3 read();
    float calibrate(Vec3 mag, float gain = 0.0001);
    void resetCalibration();

};



class BMX055 {
public:
    Accelerometer Accl;
    Gyroscope     Gyro;
    Magnetometer  Mag;

    BMX055(SPI_HandleTypeDef& spi,
    		GPIO_TypeDef* accl_cs_port, uint16_t accl_cs_pin,
			GPIO_TypeDef* gyro_cs_port, uint16_t gyro_cs_pin,
			GPIO_TypeDef* mag_cs_port, uint16_t mag_cs_pin);

    bool begin();
    void reset();
};



#endif /* INC_BMX055_HPP_ */
