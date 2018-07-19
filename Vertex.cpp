#include "Vertex.h"

Vertex::Vertex(float4 &position)
{
    this->position = position;
    this->color = float4();
}

Vertex::Vertex(float4 &position, float4 &color)
{
    this->position = position;
    this->color = color;
}

float4 &
Vertex::getPosition()
{
    return this->position;
}

float4 &
Vertex::getColor()
{
    return this->color;
}

std::string
Vertex::toString()
{
    std::stringstream ss;

    ss << "Vertex {" << std::endl
       << "  position: " << this->position.toString() << std::endl
       << "  color:    " << this->color.toString() << std::endl
       << "}" << std::endl
            ;

    return ss.str();
}
