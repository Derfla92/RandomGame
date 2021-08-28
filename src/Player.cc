#include "Player.h"
#include "SFML/Graphics.hpp"
#include "math.h"
#include "Game.h"
#include "Node.h"
#include <iostream>
#include "Transform.h"
#include "GameObject.h"
#include "Sprite2D.h"

Player::Player()
    : Entity()
{
}

void Player::Start()
{
    Entity::Start();
}

void Player::Update()
{
    Movement();
}


