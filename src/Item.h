#ifndef ITEM_H
#define ITEM_H

#include "Component.h"

class Item : public Component
{
    public:
    Item();

    virtual void Start() override;
    virtual void Update() override;
    

};

#endif
