#include "pch.h"
#include "Pos3Handler.h"

std::string
Pos3Handler::toString(const Pos3 *vertex)
{
    std::stringstream sstream;

    sstream << "{ " << vertex->x << ", " << vertex->y << ", " << vertex->z << " }";

    return sstream.str();
}

Pos3
Pos3Handler::subtract(Pos3 &v1, Pos3 &v2)
{
    Pos3 result{ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };

    return result;
}

Pos3
Pos3Handler::negate(Pos3 &v)
{
    Pos3 result{ -v.x, -v.y, -v.z };

    return result;
}

float
Pos3Handler::dotProduct(Pos3 &a, Pos3 &b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

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

float
Pos3Handler::lengthSquared(Pos3 &position)
{
    return (position.x * position.x) + (position.y * position.y) + (position.z * position.z);
}

Pos3
Pos3Handler::perpendicular(Pos3 &position)
{
    Pos3 result{ -position.y, position.x, position.z };

    return result;
}
