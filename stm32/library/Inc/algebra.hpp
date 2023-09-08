/*
 * algebra.hpp
 *
 *  Created on: Jun 19, 2022
 *      Author: yuuki.fj
 */

#ifndef ALGEBRA_HPP_
#define ALGEBRA_HPP_

class Vec3 {
public:
    float x;
    float y;
    float z;

    Vec3(): x(0), y(0), z(0) {};
    Vec3(float x, float y, float z): x(x), y(y), z(z) {};

    Vec3 operator+(const Vec3 &v) const { return Vec3(*this) += v; };
    Vec3 operator-(const Vec3 &v) const { return Vec3(*this) -= v; };
    Vec3 operator*(float a) const { return Vec3(*this) *= a; };
    Vec3 operator/(float a) const { return Vec3(*this) /= a; };
    Vec3 operator-() const { return Vec3() -= (*this); };
    Vec3 operator+() const { return Vec3(*this); };
    float operator[](unsigned i) const;
    float & operator[](unsigned i);

    Vec3 & operator=(const Vec3 &rhs) {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        return *this;
    }
    Vec3 & operator+=(const Vec3 &v);
    Vec3 & operator-=(const Vec3 &v);
    Vec3 & operator*=(float a);
    Vec3 & operator/=(float a);

    float dot(const Vec3 &v) const;

    float norm() const;
    Vec3 normalized() const;

    void show(char* buf) const;

    static const Vec3 e_x;
    static const Vec3 e_y;
    static const Vec3 e_z;
    static const Vec3 zero;
};

class Quaternion {
public:
    float x;
    float y;
    float z;
    float w;

    Quaternion() { w = 1; x = y = z = 0; };
    Quaternion(float x, float y, float z, float w): x(x), y(y), z(z), w(w) {};
    Quaternion(const Vec3 &v) { w = 0; x = v.x; y = v.y; z = v.z; };

    static Quaternion fromEuler(float x, float y, float z);

    Quaternion operator*(const Quaternion &q) const {
        return Quaternion(*this) *= q;
    };
    Quaternion operator*(const Vec3 &v) const {
        return Quaternion(*this) *= Quaternion(v);
    }

    float operator[](unsigned i) const;
    float & operator[](unsigned i);

    Quaternion & operator=(const Quaternion &rhs) {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        w = rhs.w;
        return *this;
    }
    Quaternion & operator*=(const Quaternion &q);

    Quaternion inverse() const;
    Vec3 rotate(Vec3 &v) const;

    float roll() const;
    float pitch() const;
    float yaw() const;

    void show(char* buf) const;
};


float latitudeDistance(float lat);
float longitudeDistance(float lng, float lat);
Vec3  ENU_between_LLH(Vec3 a_LLH, Vec3 b_LLH);

template <int size>
class Vector {
private:
    float *values;
    float allocated;

public:
    Vector();
    Vector(float* values);
    ~Vector();

    float operator[](unsigned i) const { return values[i]; };
    float& operator[](unsigned i) { return values[i]; } ;
};


template <int rows, int cols>
class Matrix {
public:
    const float *values;

    Matrix();
    ~Matrix();

    template <int cols2>
    Matrix<rows, cols2> operator*(Matrix<cols, cols2> &m) const;

    const Vector<cols> operator[](unsigned i) const;
    Vector<cols> operator[](unsigned i);
};



#endif /* ALGEBRA_HPP_ */
