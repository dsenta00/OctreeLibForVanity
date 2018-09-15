//
// Created by dse on 25.8.2018..
//
#include "Octree/Octree.h"

int main()
{

    std::cout << "Problem";

    auto pos0 = float4(-1.0f, 0.0f, 1.0f, 0.0f);
    auto pos1 = float4(0.0f, 0.0f, 1.0f, 0.0f);
    auto pos2 = float4(1.0f, 0.0f, 1.0f, 0.0f);
    auto pos3 = float4(1.0f, 1.0f, 1.0f, 0.0f);

    Octree octree;

    octree.insert(pos0);
    octree.insert(pos1);
    octree.insert(pos2);
    octree.insert(pos3);

    octree.print();

    return 0;
}