#ifndef CLOTHING_H
#define CLOTHING_H

#include "Item.h"

class Clothing : public Item
{
    public:
    Clothing();

    virtual void Start() override;
    virtual void Update() override;
    

    
};

#endif