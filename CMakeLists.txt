cmake_minimum_required(VERSION 3.10)
project(OctTree)

set(CMAKE_CXX_STANDARD 11)

add_library(OctTree Octree.cpp Octree.h OctreeLeaf.cpp OctreeLeaf.h Vertex.cpp Vertex.h Vector4.h Vector4.cpp Model.cpp Model.h)