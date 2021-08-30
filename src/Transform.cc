#include "Transform.h"
#include "GameObject.h"

Transform::Transform()
: position{sf::Vector2f{0,0}},localPosition{sf::Vector2f{0,0}},rotation{sf::Vector2f{0,0}},size{sf::Vector2f{1,1}}
{
    
}

Transform::Transform(sf::Vector2f position)
: position{position},localPosition{sf::Vector2f{0,0}},rotation{sf::Vector2f{0,0}},size{sf::Vector2f{1,1}}
{
    
}

void Transform::Start()
{
    
}

void Transform::Update()
{ 
    if(gameObject->parent != nullptr)
    {
        position = gameObject->parent->transform->position + localPosition;
    }
}

void Transform::MoveTo(sf::Vector2f newPos)
{
    if(gameObject->parent != nullptr)
    {
        localPosition += newPos;
    }
    else
    {
        position += newPos;
    }
}