#include "Transform.h"

Transform::Transform()
: position{sf::Vector2<double>{0,0}},rotation{sf::Vector2<double>{0,0}},size{sf::Vector2<double>{1,1}}
{
    
}

Transform::Transform(sf::Vector2<double> position)
: position{position},rotation{sf::Vector2<double>{0,0}},size{sf::Vector2<double>{1,1}}
{
    
}

void Transform::Start()
{
    
}

void Transform::Update()
{

}