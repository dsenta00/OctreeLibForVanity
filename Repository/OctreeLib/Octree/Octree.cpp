#include "pch.h"
#include "Octree.h"
#include "OctreeHandler.h"

Octree::Octree()
{
    this->root = nullptr;
    this->count = 0;
}

void
Octree::insert(const DirectX::VertexPositionColor *position)
{
    this->root = OctreeHandler::insert(new OctreeLeaf(position), this->root);
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

    OctreeHandler::print(this->root);
}

void
Octree::clear()
{
    OctreeHandler::erase(this->root);

    this->root = nullptr;
    this->count = 0;
}

Octree::~Octree()
{
    this->clear();
}

OctreeLeaf *
Octree::findNearest(DirectX::XMFLOAT3 &position)
{
    std::vector<OctreeLeaf *> vertices;

    OctreeHandler::findNearest(vertices, position, this->root);

    return vertices.empty() ? nullptr : vertices.back();
}


bool 
Octree::collidesWith(Octree &anotherOctree)
{
    return OctreeHandler::collides(this, &anotherOctree);
}