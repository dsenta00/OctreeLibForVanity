position
position
//
// Created by dse on 25.8.2018..
//

#include "pch.h"
#include "OctreeHandler.h"

/**
*
* @param leaf
* @param current
* @return
*/
OctreeLeaf *
OctreeHandler::insert(OctreeLeaf *leaf, OctreeLeaf *current)
{
    if (current == nullptr)
    {
        return leaf;
    }

    uint8_t index = current->route(leaf);
    (*current)[index] = OctreeHandler::insert(leaf, (*current)[index]);

    return current;
}

void 
OctreeHandler::erase(OctreeLeaf *current)
{
    if (current == nullptr)
    {
        return;
    }

    for (auto child : *current)
    {
        OctreeHandler::erase(child);
    }

    delete current;
}

void 
OctreeHandler::print(OctreeLeaf *leaf)
{
    if (leaf == nullptr)
    {
        return;
    }

    for (auto &child : *leaf)
    {
        OctreeHandler::print(child);
    }

    std::cout << leaf->toString() << std::endl;
}

void 
OctreeHandler::findNearest(std::vector<OctreeLeaf *> &vertices, DirectX::XMFLOAT3 &position, OctreeLeaf *current)
{
    if (current == nullptr)
    {
        return;
    }

    auto currentClosest = vertices.front();

    if ((vertices.empty()) || (current->distanceFrom(position) < currentClosest->distanceFrom(position)))
    {
        vertices.insert(vertices.begin(), current);

        for (OctreeLeaf *leaf : *current)
        {
            OctreeHandler::findNearest(vertices, position, leaf);
        }
    }
}

bool 
OctreeHandler::collides(Octree *o1, Octree *o2)
{
    //
    // TODO: Implement me
    //

    return false;
}


std::string 
OctreeHandler::XMFLOAT3_ToString(const DirectX::XMFLOAT3 *vertex)
{
    std::stringstream sstream;

    sstream << "{ " << vertex->x << ", " << vertex->y << ", " << vertex->z << " }";

    return sstream.str();
}