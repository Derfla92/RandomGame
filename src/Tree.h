#ifndef TREE_H
#define TREE_H

#include "Enviroment.h"

class Tree : public Enviroment
{
    public:
    Tree();

    private:
    void Start() override;
    void Update() override;

};

#endif