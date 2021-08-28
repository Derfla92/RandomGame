#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity
{
    public:

    Player();
    
    void Start() override;
    void Update() override;

    private:



};


#endif