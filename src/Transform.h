#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <SFML/Graphics.hpp>
#include "Component.h"


class Transform : public Component
{
    public:
    Transform();
    Transform(sf::Vector2<double>);

    void Start() override;
    void Update() override;

    sf::Vector2<double> position;
    sf::Vector2<double> rotation;
    sf::Vector2<double> size;
    private:

};

#endif