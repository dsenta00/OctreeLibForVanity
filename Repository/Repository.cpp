#include "pch.h"
#include "Repository.h"
#include "Utilities.h"
#include "Repository/OctreeLib/Octree/OctreeHandler.h"

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

        createdName.clear();
        createdName << name << " (" << i << ")" ;
    }

    return createdName.str();
}

// PUBLIC FUNCTIONS

void
Repository::create(std::string name)
{
    int i = 0;
    std::string persistName = createUniqueName(name);

    repo[persistName] = std::shared_ptr<Octree>(new Octree());
}

void 
Repository::addNewVertex(std::string name, const DirectX::VertexPositionColor *vertex)
{
    Octree *tree = Repository::get(name);

    if (!tree)
    {
        // TODO: Add DebugPrint instead of std::cout
        std::cout << "Failed to insert vertex " << OctreeHandler::XMFLOAT3_ToString(&vertex->position);
        return;
    }

    tree->insert(vertex);
}


Octree *get(std::string name)
{
    auto it = repo.find(name);

    return it == repo.end() ? nullptr : it->second.get();
}

std::vector<Octree *> 
Repository::get()
{
    std::vector<Octree *> result;

    for (auto item : repo)
    {
        result.push_back(item.second.get());
    }

    return result;
}