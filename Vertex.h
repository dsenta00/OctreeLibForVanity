#pragma once

#include "Vector4.h"
#include <string>
#include <sstream>

class Vertex {
public:
    Vertex(float4 &position);
    Vertex(float4 &position, float4 &color);
    float4 &getPosition();
    float4 &getColor();
    std::string toString();
protected:
    float4 position;
    float4 color;
};