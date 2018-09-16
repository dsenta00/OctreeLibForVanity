#pragma once

#include "pch.h"
#include "OctreeLib\Octree\Octree.h"

namespace Repository {

    /**
     * Creates new Octree
     *
     * @param name - suggested name
     *
     * @retval std::string - the persisted name.
     */
    std::string create(std::string name);

    /**
     * Add new vertex into Octree.
     *
     * @param name - octree name
     * @param vertex - the vertex
     */
    void addNewVertex(std::string name, const Vertex *vertex);

    Octree *get(std::string name);

    std::vector<Octree *> get();
}