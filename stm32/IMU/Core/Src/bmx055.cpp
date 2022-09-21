/*
 * BMX055.c
 *
 *  Created on: May 26, 2022
 *      Author: yuuki.fj
 */


#include "bmx055.hpp"

BMX055::BMX055(SPI_HandleTypeDef& spi,
		GPIO_TypeDef* accl_cs_port, uint16_t accl_cs_pin,
		GPIO_TypeDef* gyro_cs_port, uint16_t gyro_cs_pin,
		GPIO_TypeDef* mag_cs_port, uint16_t mag_cs_pin):
				Accl(Accelerometer(spi, accl_cs_port, accl_cs_pin)),
				Gyro(Gyroscope(spi, gyro_cs_port, gyro_cs_pin)),
				Mag(Magnetometer(spi, mag_cs_port, mag_cs_pin)) {}


bool BMX055::begin() {

    Accl.setRange(PM2G);
    HAL_Delay(100);
    Accl.writeRegister(0x10, 0b1100);
    HAL_Delay(100);
    Accl.writeRegister(0x11, 0x00);
    HAL_Delay(100);


    Gyro.setRange(PM125DPS);
    HAL_Delay(100);
    Gyro.writeRegister(0x10, 0x07);
    HAL_Delay(100);
    Gyro.writeRegister(0x11, 0x00);
    HAL_Delay(100);


    Mag.writeRegister(0x4B, 0x83);
    HAL_Delay(100);
    Mag.writeRegister(0x4B, 0x01);
    HAL_Delay(100);
    Mag.writeRegister(0x4C, 0x00);
    HAL_Delay(100);
    Mag.writeRegister(0x4E, 0x84);
    HAL_Delay(100);
    Mag.writeRegister(0x51, 0x04);
    HAL_Delay(100);
    Mag.writeRegister(0x52, 0x0F);
    HAL_Delay(100);

	uint8_t accl_id = Accl.readRegister(0);
	uint8_t gyro_id = Gyro.readRegister(0);
	uint8_t mag_id = Mag.readRegister(0x40);

	Accl.ok = accl_id == 0b11111010;
	Gyro.ok = gyro_id == 0x0F;
	Mag.ok  = mag_id != 0b0011001;

	if (!Accl.ok || !Gyro.ok || !Mag.ok)
		return false;

    return true;
}

void BMX055::reset() {

}


// Function ====================================================================

Function::Function(SPI_HandleTypeDef& spi, GPIO_TypeDef* cs_port, uint16_t cs_pin):
		spi(spi), cs_port(cs_port), cs_pin(cs_pin) {}

void Function::start() {
	HAL_GPIO_WritePin(cs_port, cs_pin, GPIO_PIN_RESET);
//	HAL_Delay(1);
}

void Function::end() {
//	HAL_Delay(1);
	HAL_GPIO_WritePin(cs_port, cs_pin, GPIO_PIN_SET);
//	HAL_Delay(1);
}

void Function::writeRegister(uint8_t addr, uint8_t value) {
	addr = addr & 0x7F;

	start();
	HAL_SPI_Transmit(&spi, &addr, 1, 100);
	HAL_SPI_Transmit(&spi, &value, 1, 100);
	end();
}

uint8_t Function::readRegister(uint8_t addr) {
	addr = addr | 0x80;
	uint8_t value;

	start();
	HAL_SPI_Transmit(&spi, &addr, 1, 100);
	HAL_SPI_Receive(&spi, &value, 1, 100);
	end();

	return value;
}

uint8_t Function::readRegisters(uint8_t addr, uint8_t* data, uint8_t len) {
	addr = addr | 0x80;

	start();
	HAL_SPI_Transmit(&spi, &addr, 1, 100);

	uint8_t received = 0;
	for (int n = 0; n < len; n++) {
		if (HAL_SPI_Receive(&spi, data + n, 1, 100) != HAL_OK) break;
		received++;
	}
	end();

	return received;
}


// Accelerometer ===============================================================
Accelerometer::Accelerometer(SPI_HandleTypeDef& spi, GPIO_TypeDef* cs_port, uint16_t cs_pin):
		Function(spi, cs_port, cs_pin) {}

void Accelerometer::setRange(AcclRange range) {
    uint8_t value;
    switch (range) {
    case PM4G:
        value = 0b0101; break;
    case PM8G:
        value = 0b1000; break;
    case PM16G:
        value = 0b1100; break;
    default:
        value = 0x0011;
    }
    writeRegister(0x0F, value);

    factor = 0.00980665 / 2 * range;
}

Vec3 Accelerometer::read() {
    uint8_t data[6];
    readRegisters(2, data, 6);

    ok = false;
    for (int i = 0; i < 6; i++) {
    	ok = ok || (data[i] != 0);
    }

    // Convert the data to 12-bits
    int x = ((unsigned)data[1] << 4) + ((unsigned)data[0] >> 4);
    if (x > 2047) x -= 4096;
    int y = ((unsigned)data[3] << 4) + ((unsigned)data[2] >> 4);
    if (y > 2047) y -= 4096;
    int z = ((unsigned)data[5] << 4) + ((unsigned)data[4] >> 4);
    if (z > 2047) z -= 4096;

    return { x * factor, y * factor, z * factor };
}


// Gyroscope ===================================================================
Gyroscope::Gyroscope(SPI_HandleTypeDef& spi, GPIO_TypeDef* cs_port, uint16_t cs_pin):
		Function(spi, cs_port, cs_pin) {}

Vec3 Gyroscope::read() {
    uint8_t data[6];
    readRegisters(2, data, 6);

    ok = false;
    for (int i = 0; i < 6; i++) {
    	ok = ok || (data[i] != 0);
    }

    // Convert the data
    int x = ((unsigned)data[1] << 8) + (unsigned)data[0];
    if (x > 32767) x -= 65536;
    int y = ((unsigned)data[3] << 8) + (unsigned)data[2];
    if (y > 32767) y -= 65536;
    int z = ((unsigned)data[5] << 8) + (unsigned)data[4];
    if (z > 32767) z -= 65536;

    return { x * factor, y * factor, z * factor };
}

void Gyroscope::setRange(GyroRange range) {
    uint8_t value;
    switch (range) {
    case PM2000DPS:
        value = 0b000; break;
    case PM1000DPS:
        value = 0b001; break;
    case PM500DPS:
        value = 0b010; break;
    case PM250DPS:
        value = 0b011; break;
    default:
        value = 0b100;
    }
    writeRegister(0x0F, value);

    factor = range / 32768.0;
}


// Magnetometer ================================================================
Magnetometer::Magnetometer(SPI_HandleTypeDef& spi, GPIO_TypeDef* cs_port, uint16_t cs_pin):
		Function(spi, cs_port, cs_pin) {}

Vec3 Magnetometer::read() {
    uint8_t data[6];
    readRegisters(0x42, data, 6);

    ok = false;
    for (int i = 0; i < 6; i++) {
    	ok = ok || (data[i] != 0);
    }

    // Convert the data
    int x = ((unsigned)data[1] << 5) + ((unsigned)data[0] >> 3);
    if (x > 4095) x -= 8192;
    int y = ((unsigned)data[3] << 5) + ((unsigned)data[2] >> 3);
    if (y > 4095) y -= 8192;
    int z = ((unsigned)data[5] << 7) + ((unsigned)data[4] >> 1);
    if (z > 16383) z -= 32768;

    return { (float)x / 16.0f - center.x, (float)y / 16.0f - center.y, (float)z / 16.0f - center.z };
}


float Magnetometer::calibrate(Vec3 mag, float gain) {
    float f = mag.x * mag.x + mag.y * mag.y + mag.z * mag.z - radius*radius;
    center.x += 4 * gain * f * mag.x;
    center.y += 4 * gain * f * mag.y;
    center.z += 4 * gain * f * mag.z;
    radius   += 4 * gain * f * radius;
    if (f > 1E30) resetCalibration();
    return f;
}
void Magnetometer::resetCalibration() {
  center.x = 0;
  center.y = 0;
  center.z = 0;
  radius = 10;
}

