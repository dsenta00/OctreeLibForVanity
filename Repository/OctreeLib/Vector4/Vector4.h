#pragma once

#include <cmath>
#include <string>
#include <sstream>

#define VECTOR4_SIZE (4)

template<class T>
class Vector4 {
public:

    enum Axis {
        X = 0,
        Y,
        Z,
        W
    };

    Vector4(T v0 = 0, T v1 = 0, T v2 = 0, T v3 = 0);

    T &operator[](unsigned int index);

    std::string toString();

    T length();

protected:
    T v[VECTOR4_SIZE];
};

class float4 : public Vector4<float> {
public:
    float4(float v0, float v1, float v2, float v3) : Vector4<float>(v0, v1, v2, v3)
    {}
};

template<typename T>
Vector4<T> operator-(Vector4<T> &v, Vector4<T> &m);

template<typename T>
Vector4<T> normalize(Vector4<T> &v);

template<typename T>
T distance(Vector4<T> &v1, Vector4<T> &v2);