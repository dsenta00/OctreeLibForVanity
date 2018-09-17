//
//	Octree.cpp
//  Octal tree class definition.
//
//  © 2018 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"
#include "Octree.h"
#include "OctreeHandler.h"

Octree::Octree()
{
    this->root = nullptr;
    this->count = 0;
}

void
Octree::insert(const Vertex *position)
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


void 
Octree::foreach(std::function<void(const Pos3 *position)> doSomething)
{
    OctreeHandler::iterateNext(this->root, doSomething);
}

size_t 
Octree::getCount()
{
    return this->count;
}

bool 
Octree::empty()
{
    return this->count == 0;
}

Octree::~Octree()
{
    this->clear();
}

const Pos3 * 
Octree::getRoot()
{
    return !this->root ? nullptr : this->root->getPosition();
}

const Pos3 *
Octree::furthestPointAccordingToDirection(Pos3 &direction)
{
    return OctreeHandler::furthestPointAccordingToDirection(this, direction);
}

OctreeLeaf *
Octree::findNearest(Pos3 &position)
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

Pos3 
Octree::averagePoint()
{
    return OctreeHandler::averagePoint(this);
}