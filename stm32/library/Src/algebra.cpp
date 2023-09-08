/*
 * algebra.cpp
 *
 *  Created on: Jun 19, 2022
 *      Author: yuuki.fj
 */

#include "algebra.hpp"

#include <stdio.h>
#include <math.h>

float Vec3::operator[](unsigned i) const {
    switch (i) {
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    default:
        return 0;
    }
}
float & Vec3::operator[](unsigned i) {
    switch (i) {
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    default:
        return x;
    }
}

Vec3 & Vec3::operator+=(const Vec3 &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vec3 & Vec3::operator-=(const Vec3 &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vec3 & Vec3::operator*=(float a) {
    x *= a;
    y *= a;
    z *= a;
    return *this;
}

Vec3 & Vec3::operator/=(float a) {
    x /= a;
    y /= a;
    z /= a;
    return *this;
}

float Vec3::dot(const Vec3 &v) const {
    return x * v.x + y * v.y + z * v.z;
}

float Vec3::norm() const {
    return sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::normalized() const {
    float n = norm();
    return Vec3(x / n, y / n, z / n);
}


void Vec3::show(char* buf) const {
	int x_ = (int)(x * 1000) % 1000;
	int y_ = (int)(y * 1000) % 1000;
	int z_ = (int)(z * 1000) % 1000;
    sprintf(buf, "[%d.%03d, %d.%03d, %d.%03d]", (int)x, abs(x_), (int)y, abs(y_), (int)z, abs(z_));
}


const Vec3 Vec3::e_x(1, 0, 0);
const Vec3 Vec3::e_y(0, 1, 0);
const Vec3 Vec3::e_z(0, 0, 1);
const Vec3 Vec3::zero(0, 0, 0);

Quaternion Quaternion::fromEuler(float x, float y, float z) {
    float c1 = cos(y/2);
    float c2 = cos(z/2);
    float c3 = cos(x/2);

    float s1 = sin(y/2);
    float s2 = sin(z/2);
    float s3 = sin(x/2);
    Quaternion ret;
    ret.w = c1 * c2 * c3 + s1 * s2 * s3;
    ret.x = c1 * c2 * s3 - s1 * s2 * c3;
    ret.y = s1 * c2 * c3 + c1 * s2 * s3;
    ret.z = c1 * s2 * c3 - s1 * c2 * s3;
    return ret;
}

float Quaternion::operator[](unsigned i) const {
    switch (i) {
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    case 3:
        return w;
    default:
        return 0;
    }
}
float & Quaternion::operator[](unsigned i) {
    switch (i) {
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    case 3:
        return w;
    default:
        return w;
    }
}

Quaternion & Quaternion::operator*=(const Quaternion &q) {
    Quaternion ret;
    ret.w = w*q.w - x*q.x - y*q.y - z*q.z;
    ret.x = x*q.w + w*q.x + y*q.z - z*q.y;
    ret.y = w*q.y - x*q.z + y*q.w + z*q.x;
    ret.z = w*q.z + x*q.y - y*q.x + z*q.w;
    return (*this = ret);
}

Quaternion Quaternion::inverse() const {
    float norm2 = x * x + y * y + z * z + w * w;
    return Quaternion(-x / norm2, -y / norm2, -z / norm2, w / norm2);
}

Vec3 Quaternion::rotate(Vec3 &v) const {
    Quaternion q = (*this) * Quaternion(v) * inverse();
    return Vec3(q.x, q.y, q.z);
}


float Quaternion::roll() const {
  return atan2f(w*x + y*z, 0.5f - x*x - y*y);
}
float Quaternion::pitch() const {
  return asinf(-2.0f * (x*z - w*y));
}
float Quaternion::yaw() const {
  return atan2f(x*y + w*z, 0.5f - y*y - z*z);
}

void Quaternion::show(char* buf) const {
	int x_ = (int)(x * 1000) % 1000;
	int y_ = (int)(y * 1000) % 1000;
	int z_ = (int)(z * 1000) % 1000;
	int w_ = (int)(w * 1000) % 1000;
    sprintf(buf, "[%d.%03d, %d.%03d, %d.%03d, %d.%03d]", (int)x, abs(x_), (int)y, abs(y_), (int)z, abs(z_), (int)w, abs(w_));
}


#define CIRCLES_OF_LONGITUDE 40008000.0
#define EQUATOR_RADIUS       6378137.0

float latitudeDistance(float lat) {
    return lat * CIRCLES_OF_LONGITUDE / 360.0;
}
float longitudeDistance(float lng, float lat) {
    return EQUATOR_RADIUS * cos(lat / 180.0 * M_PI) * lng / 180.0 * M_PI;
}

Vec3 ENU_between_LLH(Vec3 a_LLH, Vec3 b_LLH) {
    float lat_middle = (a_LLH.y + b_LLH.y) / 2;
    float east  = latitudeDistance(a_LLH.y - b_LLH.y);
    float north = longitudeDistance(a_LLH.x - b_LLH.x, lat_middle);
    float up    = a_LLH.z - b_LLH.z;
    return Vec3(east, north, up);
}


template <int size>
Vector<size>::Vector() {
    this->values = (float*)calloc(size, sizeof(float));
    this->allocated = true;
}

template <int size>
Vector<size>::Vector(float* values) {
    this->values = values;
    this->allocated = true;
}

template <int size>
Vector<size>::~Vector() { free(this->values); };


template <int rows, int cols>
Matrix<rows, cols>::Matrix() {
    values = (float *)calloc(rows * cols, sizeof(float));
}

template <int rows, int cols>
Matrix<rows, cols>::~Matrix() {
    free(this->values);
};

template <int rows, int cols>
template <int cols2>
Matrix<rows, cols2> Matrix<rows, cols>::operator*(Matrix<cols, cols2> &m) const {
    Matrix<rows, cols2> r;
    for (int k = 0; k < cols2; k++) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                r.values[i * cols2 + k] +=
                    this->values[i * cols + j] * m.values[j * cols + k];
            }
        }
    }
    return r;
}


template <int rows, int cols>
const Vector<cols> Matrix<rows, cols>::operator[](unsigned i) const {
    return Vector<cols>(this->values + i * cols);
}

template <int rows, int cols>
Vector<cols> Matrix<rows, cols>::operator[](unsigned i) {
    return Vector<cols>(this->values + i * cols);
}



