#ifndef OCTTREE_LIBRARY_H
#define OCTTREE_LIBRARY_H

#include <iostream>
#include <memory>
#include <vector>
#include "OctreeLeaf.h"

class Octree {
public:
    Octree();

    void insert(float4 &position);

    void insert(float4 &position, float4 &color);

    void print();

    void clear();

    Vertex *findNearest(float4 &position);

    ~Octree();

protected:
    static OctreeLeaf *insert(OctreeLeaf *leaf, OctreeLeaf *current);

    static void print(OctreeLeaf *leaf);

    static void erase(OctreeLeaf *current);

    static void findNearest(std::vector<Vertex *> &vertices, float4 &position, OctreeLeaf *current);

    OctreeLeaf *root;
    size_t count;
};

#endif