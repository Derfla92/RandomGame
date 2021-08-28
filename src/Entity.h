#ifndef ENTITY_H
#define ENTITY_H

class Node;

#include <SFML/Graphics.hpp>
#include "Component.h"
#include "PathFinding.h"


class Entity : public Component
{
    public:
    Entity();
    Entity(const Entity&);

    virtual ~Entity()=default;
    Entity& operator=(const Entity&);

    virtual void Start() override;
    virtual void FindDestination();
    virtual void SetDestination(Node*);
    std::vector<PathFinding::Node*> GetPath();


    int speed{1};

    protected:

    virtual void GetAdjacentNodes();
    void Movement();
    Node* node;
    std::vector<Node *> adjacentNodes;
    std::vector<PathFinding::Node*> path;

    

};

#endif