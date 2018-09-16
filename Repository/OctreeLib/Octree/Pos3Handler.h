#pragma once

#include "pch.h"

namespace Pos3Handler {

    std::string toString(const Pos3 *vertex);

    Pos3 subtract(Pos3 &v1, Pos3 &v2);

    Pos3 negate(Pos3 &v);

    float dotProduct(Pos3 &a, Pos3 &b);

    Pos3 tripleProduct(Pos3 &a, Pos3 &b, Pos3 &c);

    float lengthSquared(Pos3 &position);

    Pos3 perpendicular(Pos3 &ab);
}