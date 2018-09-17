//
//	Pos3Handler.h
//  Pos3 tree handler declaration.
//
//  © 2018 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#pragma once

#include "pch.h"

namespace Pos3Handler {

    /**
     * Position to string.
     *
     * @param vertex - the position pointer
     *
     * @return the string
     */
    std::string toString(const Pos3 *vertex);

    /**
     * Subtract two positions.
     *
     * @param v1 - first position
     * @param v2 - second position
     *
     * @return position result
     */
    Pos3 subtract(Pos3 &v1, Pos3 &v2);

    /**
     * Negate position (negate vector direction).
     *
     * @param v - the position
     *
     * @return position result
     */
    Pos3 negate(Pos3 &v);

    /**
     * Perform dot product of two positions.
     *
     * @param a - position "a"
     * @param b - position "b"
     *
     * @return dot product result
     */
    float dotProduct(Pos3 &a, Pos3 &b);

    /**
     * b * (a dot c) - a * (b dot c)
     *
     * @param a - the position a
     * @param b - the position b
     * @param c - the position c
     *
     * @return result of triple product
     */
    Pos3 tripleProduct(Pos3 &a, Pos3 &b, Pos3 &c);

    /**
     * Return length of position squared.
     *
     * @param position - the position
     *
     * @return |position| * |position|
     */
    float lengthSquared(Pos3 &position);

    /**
     * Return next perpendicular position according to given position.
     *
     * @param ab - input position
     *
     * @return perpendicular position 
     */
    Pos3 perpendicular(Pos3 &ab);
}