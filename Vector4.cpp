//
// Created by dse on 18.7.2018..
//

#include "Vector4.h"

template<typename T>
explicit
Vector4<T>::Vector4(T v0, T v1, T v2, T v3)
{
    this->v[Axis::X] = v0;
    this->v[Axis::Y] = v1;
    this->v[Axis::Z] = v2;
    this->v[Axis::W] = v3;
}

template<typename T>
T &
Vector4<T>::operator[](unsigned int index)
{
    return reinterpret_cast<T *>(this)[index];
}

template<typename T>
std::string
Vector4<T>::toString()
{
    std::stringstream ss;

    ss << "[ ";

    for (T &t : v)
    {
        ss << t << " ";
    }

    ss << "]";

    return ss.str();
}

template<typename T>
static T
Vector4<T>::length(Vector4<T> &a)
{
    return (T) sqrt(pow(a[Axis::X], 2) + pow(a[Axis::Y], 2) + pow(a[Axis::Z], 2));
}

template<typename T>
T
Vector4<T>::length()
{
    return Vector4<T>::length(*this);
}

template<typename T>
static T
Vector4<T>::dot(Vector4<T> &v1, Vector4<T> &v2)
{
    return (v1[Axis::X] * v2[Axis::X]) + (v1[Axis::Y] * v2[Axis::Y]) + (v1[Axis::Z] * v2[Axis::Z]);
}

template<typename T>
static Vector4<T>
Vector4<T>::cross(Vector4<T> &v1, Vector4<T> &v2)
{
    return Vector4<T>(v1[Axis::Y] * v2[Axis::Z] - v1[Axis::Z] * v2[Axis::Y],
                      v1[Axis::X] * v2[Axis::Z] - v1[Axis::Z] * v2[Axis::X],
                      v1[Axis::X] * v2[Axis::Z] - v1[Axis::Z] * v1[Axis::X],
                      0);
}

template<typename T>
Vector4<T>
operator-(Vector4<T> &v, Vector4<T> &m)
{
    return Vector4<T>(v[Vector4<T>::Axis::X] - m[Vector4<T>::Axis::X],
                      v[Vector4<T>::Axis::Y] - m[Vector4<T>::Axis::Y],
                      v[Vector4<T>::Axis::Z] - m[Vector4<T>::Axis::Z],
                      v[Vector4<T>::Axis::W] - m[Vector4<T>::Axis::W]);
}

template<typename T>
Vector4<T>
normalize(Vector4<T> &v)
{
    T length = v.length();

    return Vector4<T>(v[Vector4<T>::Axis::X] / length,
                      v[Vector4<T>::Axis::Y] / length,
                      v[Vector4<T>::Axis::Z] / length,
                      v[Vector4<T>::Axis::W] / length);
}

template<typename T>
T distance(Vector4<T> &v1, Vector4<T> &v2)
{
    return (v1 - v2).length();
}
