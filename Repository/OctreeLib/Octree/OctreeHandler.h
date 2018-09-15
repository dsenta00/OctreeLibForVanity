//
// Created by dse on 25.8.2018..
//

#ifndef OCTTREE_OCTREEHANDLER_H
#define OCTTREE_OCTREEHANDLER_H

#include "pch.h"
#include "OctreeLeaf.h"
#include "Octree.h"

/**
 *
 */
namespace OctreeHandler {

    OctreeLeaf *insert(OctreeLeaf *leaf, OctreeLeaf *current);

    void erase(OctreeLeaf *current);

    void print(OctreeLeaf *leaf);

    void findNearest(std::vector<OctreeLeaf *> &vertices, DirectX::XMFLOAT3 &position, OctreeLeaf *current);

    bool collides(Octree *o1, Octree *o2);

    std::string XMFLOAT3_ToString(const DirectX::XMFLOAT3 *vertex);
};


#endif //OCTTREE_OCTREEHANDLER_H
