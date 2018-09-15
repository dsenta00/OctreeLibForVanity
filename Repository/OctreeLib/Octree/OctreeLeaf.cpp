//
// Created by dse on 2.6.2018..
//

#include "pch.h"
#include "OctreeLeaf.h"
#include "OctreeHandler.h"

OctreeLeaf::OctreeLeaf(const DirectX::VertexPositionColor *v) : array()
{
    /* CASTING ON PURPOSE! */
    this->v = (DirectX::VertexPositionColor *)v;
    this->fill(nullptr);
}

uint8_t
OctreeLeaf::route(OctreeLeaf *leaf)
{
    auto &position = leaf->getPosition();
    auto &myPosition = this->getPosition();

    bool up = position.x > myPosition.x;
    bool east = position.y > myPosition.y;
    bool north = position.z > myPosition.z;

    return static_cast<uint8_t>(4 * up + 2 * east + north);
}

float 
OctreeLeaf::distanceFrom(OctreeLeaf &leaf)
{
    return distanceFrom(leaf.getPosition());
}

float 
OctreeLeaf::distanceFrom(DirectX::XMFLOAT3 &position)
{
    auto myPosition = this->getPosition();

    float distanceX = myPosition.x - position.x;
    float distanceY = myPosition.y - position.y;
    float distanceZ = myPosition.z - position.z;

    return sqrtf(pow(distanceX, 2) + pow(distanceY, 2) + pow(distanceZ, 2));
}

DirectX::XMFLOAT3 
OctreeLeaf::getPosition()
{
    return this->v->position;
}

std::string 
OctreeLeaf::toString()
{
    return OctreeHandler::XMFLOAT3_ToString(&v->position);
}