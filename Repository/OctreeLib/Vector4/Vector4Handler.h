//
// Created by dse on 25.8.2018..
//

#ifndef OCTTREE_VECTOR4HANDLER_H
#define OCTTREE_VECTOR4HANDLER_H


#include "Vector4.h"

class Vector4Handler {
public:
    template<typename T>
    static T length(Vector4<T> &a)
    {
        return (T) sqrt(pow(a[Vector4<T>::Axis::X], 2) +
                        pow(a[Vector4<T>::Axis::Y], 2) +
                        pow(a[Vector4<T>::Axis::Z], 2));
    }


    template<typename T>
    static T dot(Vector4<T> &v1, Vector4<T> &v2)
    {
        return (v1[Vector4<T>::Axis::X] * v2[Vector4<T>::Axis::X]) + (v1[Vector4<T>::Axis::Y] * v2[Vector4<T>::Axis::Y]) + (v1[Vector4<T>::Axis::Z] * v2[Vector4<T>::Axis::Z]);
    }

    template<typename T>
    static Vector4<T> cross(Vector4<T> &v1, Vector4<T> &v2)
    {
        return Vector4<T>(v1[Vector4<T>::Axis::Y] * v2[Vector4<T>::Axis::Z] - v1[Vector4<T>::Axis::Z] * v2[Vector4<T>::Axis::Y],
                          v1[Vector4<T>::Axis::X] * v2[Vector4<T>::Axis::Z] - v1[Vector4<T>::Axis::Z] * v2[Vector4<T>::Axis::X],
                          v1[Vector4<T>::Axis::X] * v2[Vector4<T>::Axis::Z] - v1[Vector4<T>::Axis::Z] * v1[Vector4<T>::Axis::X],
                          0);
    }
};


#endif //OCTTREE_VECTOR4HANDLER_H
