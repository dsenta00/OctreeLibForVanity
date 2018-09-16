
#include "pch.h"
#include "OctreeLib\Octree\Octree.h"

namespace Repository {
    void create(std::string name);
    void addNewVertex(std::string name, const Vertex *vertex);

    Octree *get(std::string name);
    std::vector<Octree *> get();
}