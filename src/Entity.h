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
    std::vector<Node*> GetAdjacentNodes();
    std::vector<PathFinding::Node*> GetPath();


    int speed{1};

    protected:

    virtual void SetAdjacentNodes();
    void Movement();
    void Attack();
    Node* node;
    std::vector<Node *> adjacentNodes;
    std::vector<PathFinding::Node*> path;
    
    
    sf::Time attackSpeed{sf::seconds(3)};
    sf::Time attackTimer{sf::seconds(0)};

    

};

#endif