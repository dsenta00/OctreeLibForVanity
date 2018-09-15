#ifndef OCTTREE_LIBRARY_H
#define OCTTREE_LIBRARY_H

#include "pch.h"
#include "OctreeLeaf.h"

class Octree {
public:
    Octree();

    void insert(const DirectX::VertexPositionColor *position);
    void print();
    void clear();
    OctreeLeaf *findNearest(DirectX::XMFLOAT3 &position);
    bool collidesWith(Octree &anotherOctree);
    ~Octree();

protected:
    OctreeLeaf *root;
    size_t count;
};

#endif