//
//	Repository.h
//  Repository declaration.
//
//  © 2018 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

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
    void addVertex(std::string name, const Vertex *vertex);

    /**
     * Get octree by name.
     *
     * @param name - octree name
     */
    Octree *get(std::string name);

    /**
     * Get all octrees.
     */
    std::vector<Octree *> get();
}