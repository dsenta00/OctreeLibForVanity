//
//	Repository.cpp
//  Repository definition.
//
//  © 2018 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"
#include "Repository.h"

#if defined(__cplusplus_winrt)
#include "Repository/OctreeLib/Octree/OctreeHandler.h"
#include "Repository/OctreeLib/Octree/Pos3Handler.h"
#else
#include "OctreeLib/Octree/OctreeHandler.h"
#include "OctreeLib/Octree/Pos3Handler.h"
#endif

// PRIVATE REPOSITORY GLOBAL VARIABLE
static std::map<std::string, std::shared_ptr<Octree>> repo;

// PRIVATE FUNCTIONS
static std::string
createUniqueName(std::string name)
{
    int i = 0;
    std::stringstream createdName;

    createdName << name;

    while (Repository::get(createdName.str()))
    {
        i++;

        createdName.str("");
        createdName << name << " (" << i << ")" ;
    }

    return createdName.str();
}

// PUBLIC FUNCTIONS

/**
 * Creates new Octree
 *
 * @param name - suggested name
 *
 * @retval std::string - the persisted name.
 */
std::string
Repository::create(std::string name)
{
    int i = 0;
    std::string persistName = createUniqueName(name);

    repo[persistName] = std::shared_ptr<Octree>(new Octree(name));

    return persistName;
}

/**
 * Add new vertex into Octree.
 *
 * @param name - octree name
 * @param vertex - the vertex
 */
void 
Repository::addVertex(std::string name, const Vertex *vertex)
{
    Octree *tree = Repository::get(name);

    if (!tree)
    {
        // TODO: Add DebugPrint instead of std::cout
        std::cout << "Failed to insert vertex " << Pos3Handler::toString(&vertex->position);
        return;
    }

    tree->insert(vertex);
}

/**
 * Get octree by name.
 *
 * @param name - octree name
 */
Octree *
Repository::get(std::string name)
{
    auto it = repo.find(name);

    return it == repo.end() ? nullptr : it->second.get();
}

/**
 * Get all octrees.
 */
std::vector<Octree *> 
Repository::get()
{
    std::vector<Octree *> result;

    for (var item : repo)
    {
        result.push_back(item.second.get());
    }

    return result;
}