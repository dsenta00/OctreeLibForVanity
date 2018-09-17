//
//	Octree.h
//  Octal tree class declaration.
//
//  © 2018 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#pragma once

#include "../../../pch.h"
#include "OctreeLeaf.h"

class Octree {
public:
    Octree();

    void insert(const Vertex *position);
    void print();
    void clear();
    void foreach(std::function<void(const Pos3 *position)> doSomething);
    size_t getCount();
    bool empty();
    const Pos3 *getRoot();

    OctreeLeaf *findNearest(Pos3 &position);
    const Pos3 *furthestPointAccordingToDirection(Pos3 &direction);
    Pos3 averagePoint();
    bool collidesWith(Octree &anotherOctree);

    ~Octree();
protected:
    OctreeLeaf *root;
    size_t count;
};