#ifndef ENEMY_H
#define ENEMY_H


class Node;

#include "PathFinding.h"
#include "Entity.h"

class Enemy : public Entity
{
    public:
    Enemy();
    Enemy(Node*);
    Enemy(const Enemy&);

    Enemy& operator=(const Enemy&);
    virtual void Start() override;
    virtual void Update() override;
    private:
    
    

};

#endif