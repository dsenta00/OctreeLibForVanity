//
// Created by dse on 2.6.2018..
//

#ifndef OCTREE_OCTREELEAF_H
#define OCTREE_OCTREELEAF_H

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

#endif //OCTREE_OCTREELEAF_H
