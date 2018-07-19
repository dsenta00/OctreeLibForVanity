//
// Created by dse on 2.6.2018..
//

#ifndef OCTREE_OCTREELEAF_H
#define OCTREE_OCTREELEAF_H

#include <array>
#include "Vertex.h"

#define NUMBER_OF_LEAFS (8)

class OctreeLeaf : public std::array<OctreeLeaf *, NUMBER_OF_LEAFS>, public Vertex {
public:
    OctreeLeaf(float4 &position, float4 &color);
    explicit OctreeLeaf(float4 &position);
    uint8_t route(OctreeLeaf *leaf);
};

#endif //OCTREE_OCTREELEAF_H
