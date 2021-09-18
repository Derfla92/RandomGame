#ifndef NODE_H
#define NODE_H

#include <SFML/Graphics.hpp>

class Node
{
public:
    Node();
    Node(const Node&);

    Node operator=(const Node&);

    bool isObsticle{false};
    sf::Sprite* sprite;
    sf::CircleShape* marker;
    sf::Vector2f position;

private:
};

#endif