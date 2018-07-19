#include "Octree.h"

#include <iostream>

Octree::Octree()
{
    this->root = nullptr;
    this->count = 0;
}

void
Octree::insert(float4 &position)
{
    this->root = Octree::insert(new OctreeLeaf(position), this->root);
    count++;
}

void
Octree::insert(float4 &position, float4 &color)
{
    this->root = Octree::insert(new OctreeLeaf(position, color), this->root);
    count++;
}

void
Octree::print()
{
    if (!this->root)
    {
        std::cout << "The tree is empty!" << std::endl;
        return;
    }

    Octree::print(this->root);
}

static OctreeLeaf *
Octree::insert(OctreeLeaf *leaf, OctreeLeaf *current)
{
    if (current == nullptr)
    {
        return leaf;
    }

    uint8_t index = current->route(leaf);
    (*current)[index] = Octree::insert(leaf, (*current)[index]);

    return current;
}

void
Octree::clear()
{
    Octree::erase(this->root);

    this->root = nullptr;
    this->count = 0;
}

Octree::~Octree()
{
    this->clear();
}

static void
Octree::print(OctreeLeaf *leaf)
{
    if (leaf == nullptr)
    {
        return;
    }

    for (auto &child : *leaf)
    {
        Octree::print(child);
    }

    std::cout << leaf->toString() << std::endl;
}

static void
Octree::erase(OctreeLeaf *current)
{
    if (current == nullptr)
    {
        return;
    }

    for (auto child : *current)
    {
        erase(child);
    }

    delete current;
}

Vertex *
Octree::findNearest(float4 &position)
{
    std::vector<Vertex *> vertices;

    findNearest(vertices, position, this->root);

    return vertices.empty() ? nullptr : vertices.back();
}

void
Octree::findNearest(std::vector<Vertex *> &vertices, float4 &position, OctreeLeaf *current)
{
    if (current == nullptr)
    {
        return;
    }

    if (!vertices.empty() && (distance(current->getPosition(), position) > distance(vertices.back()->getPosition(), position)))
    {
        return;
    }

    vertices.push_back(current);

    for (auto &child : *current)
    {
        Octree::findNearest(vertices, position, child);
    }
}
