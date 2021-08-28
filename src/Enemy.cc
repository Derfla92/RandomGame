#include "Enemy.h"
#include "Game.h"
#include "Node.h"
#include "math.h"
#include <iostream>
#include "PathFinding.h"
#include "GameObject.h"
#include "Transform.h"
#include "Sprite2D.h"

Enemy::Enemy()
    : Entity()
{
}

void Enemy::Start()
{
    Entity::Start();
}

void Enemy::Update()
{
    FindDestination();
    Movement();
}

