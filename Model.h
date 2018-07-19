//
// Created by dse on 18.7.2018..
//

#ifndef OCTTREE_MODEL_H
#define OCTTREE_MODEL_H

#include <string>
#include "Octree.h"

class Model : public Octree {
public:
    explicit Model(std::string name);
protected:
    std::string name;
};


#endif //OCTTREE_MODEL_H
