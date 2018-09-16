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

    void findNearest(std::vector<OctreeLeaf *> &vertices, Pos3 &position, OctreeLeaf *current);

    const Pos3 *furthestPointAccordingToDirection(Octree* o, Pos3 &direction);

    void iterateNext(OctreeLeaf *leaf, std::function<void(const Pos3 *position)> doSomething);

    Pos3 averagePoint(Octree *o);

    Pos3 minkowskiSumSupport(Octree *o1, Octree *o2, Pos3 &direction);

    bool collides(Octree *o1, Octree *o2);
};


#endif //OCTTREE_OCTREEHANDLER_H
