#include "Human.h"
#include "Game.h"
#include "Node.h"
#include "math.h"
#include <iostream>
#include "PathFinding.h"
#include "GameObject.h"
#include "Transform.h"
#include "Sprite2D.h"

Human::Human()
    : Entity()
{
}

void Human::Start()
{
    Entity::Start();
}

void Human::Update()
{
    //FindDestination();
    Movement();
    //Attack();
}

