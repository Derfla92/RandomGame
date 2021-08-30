#ifndef SHIRT_H
#define SHIRT_H

#include "Clothing.h"

class Shirt : public Clothing
{
    public:
    Shirt();

    void Update() override;
    void Start() override;

    
};

#endif