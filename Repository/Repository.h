
#include "pch.h"
#include "OctreeLib\Octree\Octree.h"

namespace Repository {
    void create(std::string name);
    void addNewVertex(std::string name, const DirectX::VertexPositionColor *vertex);

    Octree *get(std::string name);
    std::vector<Octree *> get();
}