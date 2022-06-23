/*
 * bmx055.h
 *
 *  Created on: May 26, 2022
 *      Author: yuuki.fj
 */

#ifndef INC_BMX055_HPP_
#define INC_BMX055_HPP_

#include <stdint.h>
#include <stm32f0xx_hal.h>
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
	Function(SPI_HandleTypeDef& spi);

    uint8_t begin();

    void writeRegister(uint8_t addr, uint8_t value);
    uint8_t readRegister(uint8_t addr);

//protected:
    SPI_HandleTypeDef& spi;

    virtual void sellect() = 0;
    virtual void unsellect() = 0;
};

class Accelerometer: public Function {
public:

	Accelerometer(SPI_HandleTypeDef& spi);

    Vec3 read();
    void setRange(AcclRange range);

//protected:
    void sellect();
    void unsellect();

private:
    float factor;
};

class Gyroscope: public Function {
public:
	Gyroscope(SPI_HandleTypeDef& spi);

    Vec3 read();
    void setRange(GyroRange range);

//protected:
    void sellect();
    void unsellect();

private:
    float factor;
};


class Magnetometer: public Function {
public:
	Magnetometer(SPI_HandleTypeDef& spi);

    Vec3 center;
    float radius = 10;

    Vec3 read();
    float calibrate(Vec3 mag, float gain = 0.0001);
    void resetCalibration();

//protected:
    void sellect();
    void unsellect();

};



class BMX055 {
public:
    Accelerometer Accl;
    Gyroscope     Gyro;
    Magnetometer  Mag;

    BMX055(SPI_HandleTypeDef& spi);

    uint8_t begin();
    void reset();
};



#endif /* INC_BMX055_HPP_ */
