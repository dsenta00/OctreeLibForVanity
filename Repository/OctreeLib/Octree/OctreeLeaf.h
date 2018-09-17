//
//	OctreeLeaf.h
//  Octal tree leaf declaration.
//
//  © 2018 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#pragma once

#include "../../../pch.h"

#define NUMBER_OF_LEAFS (8)

class OctreeLeaf : public std::array<OctreeLeaf *, NUMBER_OF_LEAFS> {
public:
    OctreeLeaf(const Vertex *);
    uint8_t route(OctreeLeaf *leaf);
    const Pos3 *getPosition();
    float distanceFrom(OctreeLeaf *leaf);
    float distanceFrom(const Pos3 *position);
    std::string toString();
protected:
    Vertex *v;
};