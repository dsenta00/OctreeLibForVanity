//
// Created by dse on 2.6.2018..
//

#ifndef OCTREE_OCTREELEAF_H
#define OCTREE_OCTREELEAF_H

#include "pch.h"
#include <Third Party/DirectX Tool Kit/VertexTypes.h>

#define NUMBER_OF_LEAFS (8)

class OctreeLeaf : public std::array<OctreeLeaf *, NUMBER_OF_LEAFS> {
public:
    OctreeLeaf(const DirectX::VertexPositionColor *);
    uint8_t route(OctreeLeaf *leaf);
    DirectX::XMFLOAT3 getPosition();
    float distanceFrom(OctreeLeaf &leaf);
    float distanceFrom(DirectX::XMFLOAT3 &position);
    std::string toString();
protected:
    DirectX::VertexPositionColor *v;
};

#endif //OCTREE_OCTREELEAF_H
