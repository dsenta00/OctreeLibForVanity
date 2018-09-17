//
//	OctreeHandler.cpp
//  Octal tree handler declaration.
//
//  © 2018 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#pragma once

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