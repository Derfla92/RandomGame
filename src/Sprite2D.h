#ifndef SPRITE2D_H
#define SPRITE2D_H

#include "Component.h"
#include <SFML/Graphics.hpp>

class Sprite2D : public Component
{
    public:
    Sprite2D(sf::Texture*);
    Sprite2D(const Sprite2D&);

    Sprite2D& operator=(const Sprite2D&);

    void Update() override;
    void Start() override;

    sf::Sprite* GetSprite();

    private:
    sf::Sprite* sprite;
    sf::Vector2<double> position;
    sf::Vector2<double> rotation;
    sf::Vector2<double> size;
    
};

#endif