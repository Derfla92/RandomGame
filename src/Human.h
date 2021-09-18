#ifndef HUMAN_H
#define HUMAN_H


class Node;

#include "PathFinding.h"
#include "Entity.h"

class Human : public Entity
{
    public:
    Human();
    Human(Node*);
    Human(const Human&);

    Human& operator=(const Human&);
    virtual void Start() override;
    virtual void Update() override;

    private:
    
    

};

#endif