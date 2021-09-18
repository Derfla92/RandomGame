#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <SFML/Graphics.hpp>
#include "Component.h"


class Transform : public Component
{
    public:
    Transform();
    Transform(sf::Vector2f);

    void Start() override;
    void Update() override;

    void MoveTo(sf::Vector2f);

    sf::Vector2f position;
    sf::Vector2f localPosition;
    sf::Vector2f rotation;
    sf::Vector2f size;
    private:

};

#endif