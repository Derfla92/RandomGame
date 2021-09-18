#ifndef FACTION_H
#define FACTION_H

class Entity;

#include "Component.h"
#include<string>
#include<vector>

class Faction : public Component
{
    public:
    Faction();

    void Start() override;
    void Update() override;

    std::string name;
    bool isPlayerFaction;
    std::vector<Entity*> members;
};

#endif