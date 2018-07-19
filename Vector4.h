#pragma once

#include <cmath>
#include <string>
#include <sstream>

#define VECTOR4_SIZE (4)

template<typename T>
class Vector4 {
public:

    enum Axis {
        X,
        Y,
        Z,
        W
    };

    explicit Vector4(T v0 = 0, T v1 = 0, T v2 = 0, T v3 = 0);
    T &operator[](unsigned int index);
    std::string toString();
    T length();

    static T length(Vector4<T> &a);
    static T dot(Vector4<T> &v1, Vector4<T> &v2);
    static Vector4<T> cross(Vector4<T> &v1, Vector4<T> &v2);
protected:
    T v[VECTOR4_SIZE];
};

using float4 = Vector4<float>;

template<typename T>
Vector4<T> operator-(Vector4<T> &v, Vector4<T> &m);

template<typename T>
Vector4<T> normalize(Vector4<T> &v);

template<typename T>
T distance(Vector4<T> &v1, Vector4<T> &v2);