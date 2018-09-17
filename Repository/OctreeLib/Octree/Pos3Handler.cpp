//
//	Pos3Handler.cpp
//  Pos3 tree handler definition.
//
//  © 2018 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//


#include "pch.h"
#include "Pos3Handler.h"

/**
 * Position to string.
 *
 * @param vertex - the position pointer
 *
 * @return the string
 */
std::string
Pos3Handler::toString(const Pos3 *vertex)
{
    std::stringstream sstream;

    sstream << "{ " << vertex->x << ", " << vertex->y << ", " << vertex->z << " }";

    return sstream.str();
}

/**
 * Subtract two positions.
 *
 * @param v1 - first position
 * @param v2 - second position
 *
 * @return position result
 */
Pos3
Pos3Handler::subtract(Pos3 &v1, Pos3 &v2)
{
    Pos3 result{ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };

    return result;
}

/**
 * Negate position (negate vector direction).
 *
 * @param v - the position
 *
 * @return position result
 */
Pos3
Pos3Handler::negate(Pos3 &v)
{
    Pos3 result{ -v.x, -v.y, -v.z };

    return result;
}

/**
 * Perform dot product of two positions.
 *
 * @param a - position "a"
 * @param b - position "b"
 *
 * @return dot product result
 */
float
Pos3Handler::dotProduct(Pos3 &a, Pos3 &b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

/**
 * b * (a dot c) - a * (b dot c)
 *
 * @param a - the position a
 * @param b - the position b
 * @param c - the position c
 *
 * @return result of triple product
 */
Pos3
Pos3Handler::tripleProduct(Pos3 &a, Pos3 &b, Pos3 &c)
{
    Pos3 r;

    float ac = dotProduct(a, c); // perform a.dot(c)
    float bc = dotProduct(b, c); // perform b.dot(c)

    // perform b * a.dot(c) - a * b.dot(c)
    r.x = b.x * ac - a.x * bc;
    r.y = b.y * ac - a.y * bc;
    r.z = b.z * ac - a.z * bc;

    return r;
}

/**
 * Return length of position squared.
 *
 * @param position - the position
 *
 * @return |position| * |position|
 */
float
Pos3Handler::lengthSquared(Pos3 &position)
{
    return (position.x * position.x) + (position.y * position.y) + (position.z * position.z);
}

/**
 * Return next perpendicular position according to given position.
 *
 * @param ab - input position
 *  
 * @return perpendicular position
 */
Pos3
Pos3Handler::perpendicular(Pos3 &position)
{
    Pos3 result{ -position.y, position.x, position.z };

    return result;
}
