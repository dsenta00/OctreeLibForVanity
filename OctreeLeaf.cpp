//
// Created by dse on 2.6.2018..
//

#include "OctreeLeaf.h"

OctreeLeaf::OctreeLeaf(float4 &position, float4 &color) : array(), Vertex(position,color)
{
    this->fill(nullptr);
}

explicit
OctreeLeaf::OctreeLeaf(float4 &position) : array(), Vertex(position)
{
    this->fill(nullptr);
}

uint8_t
OctreeLeaf::route(OctreeLeaf *leaf)
{
    auto &position = leaf->getPosition();
    auto &myPosition = this->getPosition();

    bool up = position[Vector4::X] > myPosition[Vector4::X];
    bool east = position[Vector4::Y] > myPosition[Vector4::Z];
    bool north = position[Vector4::Z] > myPosition[Vector4::Z];

    return static_cast<uint8_t>(4 * up + 2 * east + north);
}