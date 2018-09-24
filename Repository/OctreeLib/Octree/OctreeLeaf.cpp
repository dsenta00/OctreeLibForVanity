//
//	OctreeLeaf.cpp
//  Octal tree leaf definition.
//
//  © 2018 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"
#include "OctreeLeaf.h"
#include "OctreeHandler.h"
#include "Pos3Handler.h"

OctreeLeaf::OctreeLeaf(const Vertex *v) : array()
{
    /* CASTING ON PURPOSE! */
    this->v = (Vertex *)v;
    this->fill(nullptr);
}

uint8_t
OctreeLeaf::route(OctreeLeaf *leaf)
{
    auto position = leaf->getPosition();
    auto myPosition = this->getPosition();

    bool up = position->x > myPosition->x;
    bool east = position->y > myPosition->y;
    bool north = position->z > myPosition->z;

    return static_cast<uint8_t>(4 * up + 2 * east + north);
}

float 
OctreeLeaf::distanceFrom(OctreeLeaf *leaf)
{
    return distanceFrom(leaf->getPosition());
}

float 
OctreeLeaf::distanceFrom(const Pos3 *position)
{
    auto myPosition = this->getPosition();

    float distanceX = myPosition->x - position->x;
    float distanceY = myPosition->y - position->y;
    float distanceZ = myPosition->z - position->z;

    return sqrtf(pow(distanceX, 2) + pow(distanceY, 2) + pow(distanceZ, 2));
}

const Pos3 *
OctreeLeaf::getPosition()
{
    return &this->v->position;
}

std::string 
OctreeLeaf::toString()
{
    return Pos3Handler::toString(this->getPosition());
}