#include "Sprite2D.h"
#include "GameObject.h"
#include "Transform.h"

Sprite2D::Sprite2D(sf::Texture *texture)
    : Component(),sprite{new sf::Sprite{*texture}}, position{}, rotation{}, size{}
{
    sprite->setOrigin(texture->getSize().x/2,texture->getSize().y/2);
    sprite->setScale(0.125f,0.125f);
}

void Sprite2D::Start()
{
    
}

void Sprite2D::Update()
{
    position = sf::Vector2f{gameObject->GetComponent<Transform>()->position.x * sprite->getTexture()->getSize().x * 0.125f,
                                   gameObject->GetComponent<Transform>()->position.y * sprite->getTexture()->getSize().y * 0.125f};
    sprite->setPosition(position.x,position.y);
}

sf::Sprite *Sprite2D::GetSprite()
{
    return sprite;
}